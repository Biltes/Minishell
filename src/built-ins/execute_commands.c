/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:37:16 by migupere          #+#    #+#             */
/*   Updated: 2024/05/09 12:24:244 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	run_builtin(t_shell *shell, t_exec_node *cmd)
{
	if (!ft_strcmp(cmd->tokens_argv[0]->value[0], "echo"))
		return (echo_command(cmd), 1);
	else if (!ft_strcmp(cmd->tokens_argv[0]->value[0], "cd"))
		return (cd_command(shell, cmd), 1);
	else if (!ft_strcmp(cmd->tokens_argv[0]->value[0], "pwd"))
		return (pwd_command(shell, cmd), 1);
	else if (!ft_strcmp(cmd->tokens_argv[0]->value[0], "export"))
		return (export_command(shell, cmd), 1);
	else if (!ft_strcmp(cmd->tokens_argv[0]->value[0], "unset"))
		return (unset_command(shell, cmd), 1);
	else if (!ft_strcmp(cmd->tokens_argv[0]->value[0], "env"))
		return (env_command(shell, cmd), 1);
	else if (!ft_strcmp(cmd->tokens_argv[0]->value[0], "exit"))
		return (exit_command(shell, cmd), 1);
	return (0);
}
