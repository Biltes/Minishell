/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:11:48 by migupere          #+#    #+#             */
/*   Updated: 2024/07/03 14:50:58 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd(ERROR_TITLE, STDERR_FILENO);
		perror("fork");
		return (FORK_FAILURE_EXIT_CODE);
	}
	return (pid);
}

int	check_error_and_exit(int result, char *msg, int exit_code)
{
	if (result == -1)
	{
		ft_putstr_fd(ERROR_TITLE, STDERR_FILENO);
		perror(msg);
		exit(exit_code);
	}
	return (result);
}

void	wait_children(t_shell *shell)
{
	int	status;

	if (waitpid(shell->pid, &g_exit, 0) == -1)
	{
		perror("Waitpid error");
		return ;
	}
	if (WIFEXITED(g_exit))
		g_exit = WEXITSTATUS(g_exit);
	else if (WIFSIGNALED(g_exit))
		g_exit = WTERMSIG(g_exit) + EXIT_SIG_OFFSET;
	while (wait(&status) > 0)
		;
	if (g_exit == SIGINT_EXIT_STATUS)
		shell->status = RESTORE;
}
