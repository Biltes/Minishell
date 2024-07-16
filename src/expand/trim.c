/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:14:20 by migupere          #+#    #+#             */
/*   Updated: 2024/07/16 15:43:46 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	trim_arg(char *arg)
{
	int		squote;
	int		dquote;

	dquote = 0;
	squote = 0;
	while (*arg)
	{
		if (*arg == '"' && !squote)
			dquote = !dquote;
		if (*arg == '\'' && !dquote)
			squote = !squote;
		if (ft_strchr(SPACES, *arg) && !squote && !dquote)
			*arg = '\0';
		arg++;
	}
}

void	trim_quotes(char *arg, int *len)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (i < *len)
	{
		if ((arg[i] == '"' || arg[i] == '\'') && !quote)
		{
			quote = arg[i];
			ft_memmove(arg + i, arg + i + 1, *len - i);
			(*len)--;
		}
		else if (quote && arg[i] == quote)
		{
			quote = 0;
			ft_memmove(arg + i, arg + i + 1, *len - i);
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

void	process_and_trim_arg(t_shell *shell, t_token *token, int len)
{
	int		expanded;
	char	*tmp;
	char	*token_value_cpy;

	if (!token->value)
		return ;
	token_value_cpy = ft_strdup(token->value);
	expanded = (ft_strchr(token->value, '$') || \
		 ft_strchr(token->value, '*') || ft_strchr(token->value, '~'));
	expand_arg(shell, &token_value_cpy);
	if (expanded)
	{
		free(token->value);
		token->value = NULL;
		token->value = token_value_cpy;
	}
	else
		free(token_value_cpy);
	len = ft_strlen(token->value);
	trim_quotes(token->value, &len);
	tmp = token->value;
	while (tmp < token->value + len)
	{
		if (*tmp == '\0' && (ft_strcmp(token->value, \
			"printf") || token != token + 2))
			token->value = tmp + 1;
		tmp++;
	}
	if (!token->value[0] && expanded)
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
