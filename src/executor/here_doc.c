/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:30:37 by migupere          #+#    #+#             */
/*   Updated: 2024/07/18 10:51:21 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	expand_heredoc(t_shell *shell, char **line, int i, int j)
{
	char	*tmp;
	char	*env_value;

	while ((*line)[i])
	{
		if ((*line)[i] == '$' && (*line)[i + 1] == '?')
		{
			tmp = ft_itoa(g_exit);
			expander(i, i + 2, line, tmp);
			free(tmp);
		}
		else if ((*line)[i] == '$' && ft_isalpha((*line)[i + 1]))
		{
			j = i + 1;
			while (ft_isalnum((*line)[j]) || (*line)[j] == '_')
				j++;
			tmp = ft_substr(*line, i + 1, j - i - 1);
			env_value = env_get(tmp, shell);
			if (env_value)
				expander(i, j, line, env_value);
			free(tmp);
		}
		i++;
	}
}

static void	process_heredoc_lines(t_shell *shell, t_here *here, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_printf(ERROR_TITLE ERROR_HERE_DOC "%s'\n", here->eof);
			break ;
		}
		if (ft_strcmp(line, here->eof) == 0)
		{
			free(line);
			break ;
		}
		expand_heredoc(shell, &line, 0, 0);
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	g_exit = 0;
	free_exit(shell);
}

static int	setup_heredoc_file(t_here *here)
{
	int	fd;

	fd = open("here_doc", here->mode, FILE_PERMISSIONS);
	if (fd == -1)
	{
		perror("open");
		return (-1);
	}
	dup2(here->fdin, STDIN_FILENO);
	dup2(here->fdout, STDOUT_FILENO);
	return (fd);
}

static void	heredoc_reader(t_shell *shell, t_here *here, int fd)
{
	fd = setup_heredoc_file(here);
	if (fd == -1)
	{
		return ;
	}
	process_heredoc_lines(shell, here, fd);
}

void	run_heredoc(t_shell *shell, t_here *here)
{
	int		fd;
	int		len;
	pid_t	pid;

	len = ft_strlen(here->eof);
	quotes_remove(here->eof, &len, 0, 0);
	pid = check_fork();
	if (pid == 0)
	{
		signals_set(HEREDOC, shell);
		heredoc_reader(shell, here, 0);
	}
	waitpid(pid, &g_exit, 0);
	g_exit = WEXITSTATUS(g_exit);
	fd = open("here_doc", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (g_exit == 0)
		run_cmd(shell, here->cmd);
	dup2(here->fdin, STDIN_FILENO);
	unlink("here_doc");
}
