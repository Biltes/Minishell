/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:13:12 by migupere          #+#    #+#             */
/*   Updated: 2024/05/17 17:52:45 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	point_to_exp_tilde(t_shell *sh, int point, char *tmp, char **line)
{
    char *env_var;
	char *exit_status;

    if (!tmp[1] || ft_strchr(NOT_EXP, tmp[1]))
    {
        env_var = env_get("HOME", sh);
        if (!env_var)
            return (-1);
        return (expand(env_var, point, point + 1, line));
    }
    else if (tmp[1] == '+' && (!tmp[2] || ft_strchr(NOT_EXP, tmp[2])))
    {
        env_var = env_get("PWD", sh);
        if (!env_var)
            return (-1);
        return (expand(env_var, point, point + 2, line));
    }
    else if (tmp[1] == '-' && (!tmp[2] || ft_strchr(NOT_EXP, tmp[2])))
    {
        env_var = env_get("OLDPWD", sh);
        if (!env_var)
            return (-1);
        return (expand(env_var, point, point + 2, line));
    }
    else if (*tmp == '$' && tmp[1] == '?')
    {
        exit_status = ft_itoa(g_exit);
        if (!exit_status)
            return (-1);
        return (expand_free(exit_status, point, point + 2, line));
    }
    return (0);
}

static int	expand_tilde(t_shell *shell, char **line)
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

static int	point_to_expand_env(t_shell *sh, int point, char *tmp, char **line)
{
    char	*key;
    int		len;
	char *exit_status;

    if (tmp[1] == '?')
    {
        exit_status = ft_itoa(g_exit);
        if (!exit_status)
            return (-1);
        return (expand_free(exit_status, point, point + 2, line));
    }
    else if (tmp[1])
	{
		len = 1;
		while (ft_isalpha(tmp[len]) || tmp[len] == '_')
			len++;
		len += (ft_isalnum(tmp[len]) > 0);
		while (len > 2 && (ft_isalnum(tmp[len]) || tmp[len] == '_'))
			len++;
		     key = ft_substr(tmp, 1, len - 1);
        if (!key)
            return (-1);
        char *env_var = env_get(key, sh);
        free(key);
        if (!env_var)
            return (-1);
        if (expand(env_var, point, point + len, line) == -1)
            return (-1);
        return (1);
    }
    return (0);
}

static void	env_expand(t_shell *shell, char *tmp, char **line)
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

 void expand_argv(t_shell *shell, t_token **tokens_argv)
{
    int len;
    int i;
    int expanded;
    char *tmp;

    if (!tokens_argv[0]->value)
        return;

    i = 0;
    while (tokens_argv[i])
    {
        expanded = (ft_strchr(tokens_argv[i]->value, '$') || ft_strchr(tokens_argv[i]->value, '*'));
        expand_arg(shell, &tokens_argv[i]->value);
        len = ft_strlen(tokens_argv[i]->value);
        trim_arg(tokens_argv[i]->value);
        trim_quotes(tokens_argv[i]->value, &len);

        tmp = tokens_argv[i]->value;
        while ((tmp < tokens_argv[i]->value + len) && i < (MAXARG - 1))
        {
            if (*tmp == '\0' && (ft_strcmp(tokens_argv[i]->value, "printf") || i != 2))
                tokens_argv[i + 1]->value = tmp + 1;
            tmp++;
        }
        if (!tokens_argv[i]->value[0] && expanded)
        {
            free(tokens_argv[i]->value);
            tokens_argv[i]->value = NULL;
        }
        i++;
    }
}

void	expand_arg(t_shell *shell, char **arg)
{
	expand_tilde(shell, arg);
	env_expand(shell, *arg - 1, arg);
	expand_wildcard(arg);
}

