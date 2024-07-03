/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:49:21 by migupere          #+#    #+#             */
/*   Updated: 2024/07/03 14:34:54 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	close_fds_and_signals_set(int fd[2], int sig)
{
	if (sig)
		signals_set(sig, NULL);
	check_error_and_exit(close(fd[0]), "close error", FORK_FAILURE_EXIT_CODE);
	check_error_and_exit(close(fd[1]), "close error", FORK_FAILURE_EXIT_CODE);
}

static void	run_pipe(t_shell *shell, t_ast_list *cmd)
{
	int	fd[2];

	check_error_and_exit(pipe(fd), "pipe error", FORK_FAILURE_EXIT_CODE);
	shell->pid = check_fork();
	if (shell->pid < 0)
	{
		perror("fork error");
		exit(FORK_FAILURE_EXIT_CODE);
	}
	else if (shell->pid == 0)
	{
		check_error_and_exit(dup2(fd[1], STDOUT_FILENO), \
			"dup2 error", FORK_FAILURE_EXIT_CODE);
		close_fds_and_signals_set(fd, SIGIGNORE);
		run_cmd(shell, cmd->left);
		free_exit(shell);
	}
	if (cmd->left->type == HERE_DOC)
		wait_children(shell);
	if (shell->status == CONTINUE)
		shell->pid = check_fork();
	if (shell->pid == 0)
	{
		check_error_and_exit(dup2(fd[0], STDIN_FILENO), \
		"dup2 error", FORK_FAILURE_EXIT_CODE);
		close_fds_and_signals_set(fd, SIGIGNORE);
		run_cmd(shell, cmd->right);
		free_exit(shell);
	}
	close_fds_and_signals_set(fd, 0);
	wait_children(shell);
}

void	run_cmd(t_shell *shell, t_cmd *cmd)
{
	if (cmd->type == EXEC)
		run_exec(shell, (t_exec_node *)cmd);
	else if (cmd->type == REDIR)
		run_redir(shell, (t_redir_node *)cmd);
	else if (cmd->type == HERE_DOC)
		run_heredoc(shell, (t_here *)cmd);
	else if (cmd->type == PIPE)
		run_pipe(shell, (t_ast_list *)cmd);
}
