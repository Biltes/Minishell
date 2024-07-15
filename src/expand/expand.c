/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:32:35 by migupere          #+#    #+#             */
/*   Updated: 2024/07/15 23:21:54 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	free_and_return(char *tmp)
{
	if (tmp)
		free(tmp);
	return (-1);
}

int	expand(char *key, int i, int j, char **line)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(*line, 0, i);
	if (!tmp)
		return (-1);
	tmp2 = ft_substr(*line, j, ft_strlen(*line) - j + 1);
	if (!tmp2)
		return (free_and_return(tmp));
	*line = ft_strjoin(tmp, key);
	free(tmp);
	if (!*line)
		return (free_and_return(tmp2));
	tmp = *line;
	free(*line);
	*line = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	if (!*line)
		return (-1);
	return (0);
}

int	expand_free(char *key, int i, int j, char **line)
{
	int	ret;

	ret = expand(key, i, j, line);
	free(key);
	return (ret);
}

void	expand_argv(t_shell *shell, t_token **tokens_argv)
{
	int	i;

	if (!tokens_argv[0])
		return ;
	i = 0;
	while (tokens_argv[i])
	{
		process_and_trim_arg(shell, tokens_argv[i], 0);
		i++;
	}
}

void	expand_arg(t_shell *shell, char **arg)
{
	expand_tilde(shell, arg);
	env_expand(shell, *arg - 1, arg);
}
