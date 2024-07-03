/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migupere <migupere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:49:11 by migupere          #+#    #+#             */
/*   Updated: 2024/07/03 13:49:12 by migupere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	env_command(t_shell *shell, t_exec_node *cmd)
{
	if (cmd->tokens_argv[1])
	{
		print_error(shell, "env", "too many arguments", 2);
		return ;
	}
	envp_print(shell);
	if (shell->status == CONTINUE)
		g_exit = 0;
}
