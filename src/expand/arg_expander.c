/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:49:44 by migupere          #+#    #+#             */
/*   Updated: 2024/07/18 10:51:56 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	exp_tilde_variable(t_shell *sh, char *tmp, char **line, int point)
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
	return (expander(point, point + len, line, env_var));
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

int	tilde_checker(t_shell *m_shell, char **line, int dblquote, int sgquote)
{
	char	*tmp;
	char	**tmp2;
	int		flag;

	flag = 0;
	tmp = *line;
	tmp2 = line;
	while (*tmp)
	{
		if (*tmp == '\'' && !dblquote)
			sgquote = !sgquote;
		if (*tmp == '"' && !sgquote)
			dblquote = !dblquote;
		if ((*tmp == '~' && !dblquote && !sgquote) \
			&& (tmp == *line || ft_strchr(SPACES, *(tmp - 1))))
		{
			if (exp_tilde_variable(m_shell, tmp, line, tmp - *line))
				tmp = *line;
		}
		if (*tmp)
			tmp++;
	}
	if (flag == 1)
		free(tmp2);
	return (0);
}

static int	expand_env_var(t_shell *sh, int point, char *tmp, char **line)
{
	int		len;
	char	*env_var;

	env_var = get_env_var(sh, tmp, &len);
	if (!env_var)
		return (-1);
	if (tmp[1] == '?')
		return (expand_free(env_var, point, point + 2, line));
	if (expander(point, point + len, line, env_var) == -1)
		return (-1);
	return (1);
}

void	env_checker(t_shell *m_shell, char *tmp, char **line)
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
			if (expand_env_var(m_shell, tmp - *line, tmp, line))
			{
				tmp = *line - 1;
				dblquote = 0;
				sgquote = 0;
			}
		}
	}
}
