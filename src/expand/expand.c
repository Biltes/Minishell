/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:32:35 by migupere          #+#    #+#             */
/*   Updated: 2024/07/16 13:08:05 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


int	expand(char *key, int i, int j, char **line)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_substr(*line, 0, i);
	tmp2 = ft_substr(*line, j, ft_strlen(*line) - j + 1);
	tmp3 = *line;
	free(tmp3);
	*line = ft_strjoin(tmp, key);
	free(tmp);
	tmp = *line;
	*line = ft_strjoin(*line, tmp2);
	free(tmp);
	free(tmp2);
	return (1);
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
