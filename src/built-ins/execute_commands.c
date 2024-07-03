/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:49:13 by migupere          #+#    #+#             */
/*   Updated: 2024/07/03 14:52:51 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	run_builtin(t_shell *shell, t_exec_node *cmd)
{
	if (!ft_strcmp(cmd->tokens_argv[0]->value, "echo"))
		return (echo_command(cmd), 1);
	else if (!ft_strcmp(cmd->tokens_argv[0]->value, "cd"))
		return (cd_command(shell, cmd), 1);
	else if (!ft_strcmp(cmd->tokens_argv[0]->value, "pwd"))
		return (pwd_command(shell, cmd), 1);
	else if (!ft_strcmp(cmd->tokens_argv[0]->value, "export"))
		return (export_command(shell, cmd), 1);
	else if (!ft_strcmp(cmd->tokens_argv[0]->value, "unset"))
		return (unset_command(shell, cmd), 1);
	else if (!ft_strcmp(cmd->tokens_argv[0]->value, "env"))
		return (env_command(shell, cmd), 1);
	else if (!ft_strcmp(cmd->tokens_argv[0]->value, "exit"))
		return (exit_command(shell, cmd), 1);
	return (0);
}
