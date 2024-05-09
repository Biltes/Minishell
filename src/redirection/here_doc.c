/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migupere <migupere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:30:37 by migupere          #+#    #+#             */
/*   Updated: 2024/05/09 12:53:30 by migupere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void expand_heredoc(t_shell *shell, char **line)
{
    int i;
    int j;
    char *tmp;
	char *env_value;

    i = 0;
    while ((*line)[i])
    {
        if ((*line)[i] == '$' && (*line)[i + 1] == '?')
        {
            tmp = ft_itoa(g_exit);
            expand(tmp, i, i + 2, line);
            free(tmp);
        }
        else if ((*line)[i] == '$' && ft_isalpha((*line)[i + 1]))
        {
            j = i + 1;
            while (ft_isalnum((*line)[j]) || (*line)[j] == '_')
                j++;
            tmp = ft_substr(*line, i + 1, j - i - 1);
            env_value = env_get(tmp, shell);
            expand(env_value, i, j, line);
            free(tmp);
            free(env_value);
        }
        i++;
    }
}

static void	heredoc_reader(t_shell *shell, t_here *here, int fd)
{
	char	*line;

	fd = open("here_doc", here->mode, FILE_PERMISSIONS);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	dup2(here->fdin, STDIN_FILENO);
	dup2(here->fdout, STDOUT_FILENO);
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
		expand_heredoc(shell, &line);
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	g_exit = 0;
	free_exit(shell);
}

void	run_heredoc(t_shell *shell, t_here *here)
{
	int		fd;
	int		len;
	pid_t	pid;

	len = ft_strlen(here->eof);
	trim_quotes(here->eof, &len);
	pid = check_fork();
	if (pid == 0)
	{
		signals_set(SIGHEREDOC, shell); // Pass shell to signals_set
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

t_cmd	*here_cmd(t_cmd *cmd, char *eof)
{
	t_here	*here;
	t_cmd	*tmp;
	t_cmd	*tmp2;

	here = (t_here *)ft_calloc(1, sizeof(t_here));
	here->type = HERE_DOC;
	here->eof = ft_strdup(eof);
	here->mode = O_WRONLY | O_CREAT | O_TRUNC;
	here->fdin = dup(STDIN_FILENO);
	here->fdout = dup(STDOUT_FILENO);
	if (cmd->type == EXEC || cmd->type == REDIR || cmd->type == BLOCK)
		here->cmd = cmd;
	else
	{
		tmp = cmd;
		while (tmp->type != EXEC && tmp->type != REDIR && tmp->type != BLOCK)
		{
			tmp2 = tmp;
			tmp = ((t_redir_node *)tmp)->cmd;
		}
		((t_redir_node *)tmp2)->cmd = (t_cmd *)here;
		here->cmd = tmp;
		return (cmd);
	}
	return ((t_cmd *)here);
}
