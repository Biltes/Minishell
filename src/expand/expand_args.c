/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biltes <biltes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:49:44 by migupere          #+#    #+#             */
/*   Updated: 2024/07/04 17:13:15 by biltes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	point_to_exp_tilde(t_shell *sh, int point, char *tmp, char **line)
{
	char	*env_var;
	int		len;

	env_var = get_tilde_env_var(sh, tmp);
	if (!env_var)
		return (0);
	if (*tmp == '$' && tmp[1] == '?')
		return (expand_free(env_var, point, point + 2, line));
	if (!tmp[1] || ft_strchr(NOT_EXP, tmp[1]))
		len = 1;
	else if (tmp[1] == '+' || tmp[1] == '-')
		len = 2;
	else
		len = 1;
	return (expand(env_var, point, point + len, line));
}

int	expand_tilde(t_shell *shell, char **line)
{
	int		dblquote;
	int		sgquote;
	char	*tmp;

	dblquote = 0;
	sgquote = 0;
	tmp = *line;
	while (*tmp)
	{
		if (*tmp == '"' && !sgquote)
			dblquote = !dblquote;
		if (*tmp == '\'' && !dblquote)
			sgquote = !sgquote;
		if (*tmp == '~' && !dblquote && !sgquote
			&& (tmp == *line || ft_strchr(SPACES, *(tmp - 1))))
			if (point_to_exp_tilde(shell, tmp - *line, tmp, line))
				tmp = *line;
		if (*tmp)
			tmp++;
	}
	return (0);
}

static char	*get_env_var(t_shell *sh, const char *tmp, int *len)
{
	char	*key;
	char	*env_var;

	if (tmp[1] == '?')
		return (ft_itoa(g_exit));
	else if (tmp[1])
	{
		*len = 1;
		while (ft_isalpha(tmp[*len]) || tmp[*len] == '_')
			(*len)++;
		*len += (ft_isalnum(tmp[*len]) > 0);
		while (*len > 2 && (ft_isalnum(tmp[*len]) || tmp[*len] == '_'))
			(*len)++;
		key = ft_substr(tmp, 1, *len - 1);
		if (!key)
			return (NULL);
		env_var = env_get(key, sh);
		free(key);
		return (env_var);
	}
	return (NULL);
}

static int	point_to_expand_env(t_shell *sh, int point, char *tmp, char **line)
{
	int		len;
	char	*env_var;

	env_var = get_env_var(sh, tmp, &len);
	if (!env_var)
		return (-1);
	if (tmp[1] == '?')
		return (expand_free(env_var, point, point + 2, line));
	if (expand(env_var, point, point + len, line) == -1)
		return (-1);
	return (1);
}

void	env_expand(t_shell *shell, char *tmp, char **line)
{
	int		dblquote;
	int		sgquote;

	dblquote = 0;
	sgquote = 0;
	while (*(++tmp))
	{
		if (*tmp == '"' && !sgquote)
			dblquote = !dblquote;
		if (*tmp == '\'' && !dblquote)
			sgquote = !sgquote;
		if (*tmp == '$' && !ft_strchr(NOT_EXP, *(tmp + 1)) && !sgquote
			&& !((dblquote || sgquote) && (*(tmp + 1) == '"'
					|| *(tmp + 1) == '\'')))
		{
			if (point_to_expand_env(shell, tmp - *line, tmp, line))
			{
				tmp = *line - 1;
				dblquote = 0;
				sgquote = 0;
			}
		}
	}
}
