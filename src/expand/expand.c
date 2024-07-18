/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:32:35 by migupere          #+#    #+#             */
/*   Updated: 2024/07/18 10:54:45 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	expander(int i, int j, char **line, char *key)
{
	char	*line_prefix;
	char	*line_suffix;
	char	*old_line;

	line_prefix = ft_substr(*line, 0, i);
	line_suffix = ft_substr(*line, j, ft_strlen(*line) - j + 1);
	old_line = *line;
	free(old_line);
	*line = ft_strjoin(line_prefix, key);
	free(line_prefix);
	line_prefix = *line;
	*line = ft_strjoin(*line, line_suffix);
	free(line_prefix);
	free(line_suffix);
	return (1);
}

int	expand_free(char *key, int i, int j, char **line)
{
	int	ret;

	ret = expander(i, j, line, key);
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
		args_process(shell, tokens_argv[i], 0, 0);
		i++;
	}
}

void	expand_arg(t_shell *shell, char **arg)
{
	tilde_checker(shell, arg, 0, 0);
	env_checker(shell, *arg - 1, arg);
}
