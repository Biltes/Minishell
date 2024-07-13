/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_errors2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:30:18 by migupere          #+#    #+#             */
/*   Updated: 2024/07/13 13:57:32 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	print_error(t_shell *shell, char *msg, char *msg2, int exit)
{
	ft_putstr_fd(ERROR_TITLE, STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	if (msg2)
		ft_putstr_fd(": ", STDERR_FILENO);
	else
		ft_putchar_fd('\n', STDERR_FILENO);
	ft_putendl_fd(msg2, STDERR_FILENO);
	shell->status = RESTORE;
	g_exit = exit;
	return (1);
}

int	error_in(t_shell *shell, char *cmd, char *arg, int error_code)
{
	char	*error;

	error = ft_strjoin(cmd, arg);
	print_error(shell, error, "not a valid identifier", error_code);
	free(error);
	return (0);
}

void	free_exit(t_shell *shell)
{
	if (shell->lexer)
	{
		if (shell->lexer->str)
			free(shell->lexer->str);
		free(shell->lexer);
	}
	if (shell->input)
	{
		free(shell->input);
		shell->input= NULL;
	}
	if (shell->ast)
		free_cmd(shell->ast);
	envp_destroy(shell->env);
	if (shell->envp)
		free_array(shell->envp);
	exit(g_exit);
}
