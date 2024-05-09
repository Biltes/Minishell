/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migupere <migupere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:55:40 by migupere          #+#    #+#             */
/*   Updated: 2024/05/09 12:53:30 by migupere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_contains_only(char *str, char *characters)
{
    while (*str)
    {
        if (!ft_strchr(characters, *str++))
            return (0);
    }
    return (1);
}

static int	echo_flag(t_exec_node *cmd, int *arg_index)
{
    while (cmd->tokens_argv[++i]->value[0])
    {
        if (cmd->tokens_argv[i]->value[0] != '-')
            break;
        if (!ft_contains_only(&cmd->tokens_argv[i]->value[1], "n"))
            break;
        return 1;
    }
    return 0;
}

static void print_arguments(t_exec_node *cmd, int start_index)
{	
	int	i;
	ft_putstr_fd(cmd->tokens_argv[i]->value[0], STDOUT_FILENO);
	i = start_index + 1;
	while (cmd->tokens_argv[i])
	{
		ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd(cmd->tokens_argv[i]->value[0], STDOUT_FILENO);
		i++;
	}
}

void echo_command(t_exec_node *cmd)
{
    int	i = 0;
    int	flag = echo_flag(cmd, &i);

    if (cmd->tokens_argv[i]->value[0])
        print_arguments(cmd, i);

    if (!flag)
        ft_putchar_fd('\n', STDOUT_FILENO);

    g_exit = 0;
}