/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migupere <migupere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:37:16 by migupere          #+#    #+#             */
/*   Updated: 2024/04/15 16:08:42 by migupere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	run_builtin(t_shell *shell, t_exec *cmd)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (echo_command(cmd), 1);
	else if (!ft_strcmp(cmd->argv[0], "cd"))
		return (cd_command(shell, cmd), 1);
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (pwd_command(shell, cmd), 1);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		return (export_command(shell, cmd), 1);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		return (unset_command(shell, cmd), 1);
	else if (!ft_strcmp(cmd->argv[0], "env"))
		return (env_command(shell, cmd), 1);
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		return (exit_command(shell, cmd), 1);
	return (0);
}
