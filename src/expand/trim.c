/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:14:20 by migupere          #+#    #+#             */
/*   Updated: 2024/07/03 14:08:43 by pevieira         ###   ########.fr       */
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
			memmove(arg + i, arg + i + 1, *len - i);
			(*len)--;
		}
		else if (quote && arg[i] == quote)
		{
			quote = 0;
			memmove(arg + i, arg + i + 1, *len - i);
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
