/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:14:20 by migupere          #+#    #+#             */
/*   Updated: 2024/07/18 10:26:57 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	quotes_remove(char *str, int *len, int i, char quote)
{
	while (i < *len)
	{
		if (quote && str[i] == quote)
		{
			quote = 0;
			ft_memmove(str + i, str + i + 1, *len - i);
			(*len)--;
		}
		else if ((str[i] == '\'' || str[i] == '"') && !quote)
		{
			quote = str[i];
			ft_memmove(str + i, str + i + 1, *len - i);
			(*len)--;
		}
		else
			i++;
	}
}

char	**convert_tokens_to_argv(t_token **tokens)
{
	int		i;
	int		j;
	char	**argv;

	i = 0;
	while (tokens[i] != NULL)
		i++;
	argv = malloc((i + 1) * sizeof(char *));
	if (!argv)
		return (NULL);
	j = 0;
	while (j < i)
	{
		argv[j] = tokens[j]->value;
		j++;
	}
	argv[i] = NULL;
	return (argv);
}

void	trimming(char *str, int squote, int dquote)
{
	while (*str)
	{
		if (*str == '"' && !squote)
			dquote = !dquote;
		if (*str == '\'' && !dquote)
			squote = !squote;
		if (ft_strchr(SPACES, *str) && !squote && !dquote)
			*str = '\0';
		str++;
	}
}

void	args_process(t_shell *shell, t_token *token, int len, int expand)
{
	char	*token_value_cpy;

	if (!token->value)
		return ;
	token_value_cpy = ft_strdup(token->value);
	expand = (ft_strchr(token->value, '$') || \
		ft_strchr(token->value, '*') || ft_strchr(token->value, '~'));
	expand_arg(shell, &token_value_cpy);
	if (expand)
	{
		free(token->value);
		token->value = NULL;
		token->value = token_value_cpy;
	}
	else
		free(token_value_cpy);
	len = ft_strlen(token->value);
	quotes_remove(token->value, &len, 0, 0);
	if (!token->value[0] && expand)
	{
		free(token->value);
		token->value = NULL;
	}
}

char	*get_tilde_env_var(t_shell *sh, char *tmp)
{
	if (!tmp[1] || ft_strchr(NOT_EXP, tmp[1]))
		return (env_get("HOME", sh));
	else if (tmp[1] == '+' && (!tmp[2] || ft_strchr(NOT_EXP, tmp[2])))
		return (env_get("PWD", sh));
	else if (tmp[1] == '-' && (!tmp[2] || ft_strchr(NOT_EXP, tmp[2])))
		return (env_get("OLDPWD", sh));
	else if (*tmp == '$' && tmp[1] == '?')
		return (ft_itoa(g_exit));
	return (NULL);
}
