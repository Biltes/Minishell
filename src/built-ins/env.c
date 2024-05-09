/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migupere <migupere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:55:43 by migupere          #+#    #+#             */
/*   Updated: 2024/05/09 14:40:37 by migupere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	env_command(t_shell *shell, t_exec_node *cmd)
{
    // Check if any arguments are passed to the env command
    if (cmd->tokens_argv[1])
    {
        print_error(shell, "env", "too many arguments", 2);
        return;
    }

    // Print all the environment variables
    envp_print(shell);

    // The env command always succeeds
    if (shell->status == CONTINUE)
        g_exit = 0;
}
