/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:55:40 by migupere          #+#    #+#             */
/*   Updated: 2024/05/24 17:38:39 by pevieira         ###   ########.fr       */
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

static int	echo_flag(t_exec_node *cmd, int index) //Miguel pq é um pointer o int aqui????
{
	index = 0;
    while (cmd->tokens_argv[++index]->value[0])
    {
		if (!cmd->tokens_argv[index]->value[0])
		{
			break;
		}
		if (cmd->tokens_argv[index]->value[0] != '-')
			break;
		if (!ft_contains_only(&cmd->tokens_argv[index]->value[1], "n"))
			break;
		return 1;
	}
	return 0;
}


/*
static void print_arguments(t_exec_node *cmd, int start_index)
{
    int	i;
    ft_putstr_fd(cmd->tokens_argv[start_index]->value, STDOUT_FILENO);
    i = start_index + 1;
    while (cmd->tokens_argv[i])
    {
        ft_putchar_fd(' ', STDOUT_FILENO);
        ft_putstr_fd(cmd->tokens_argv[i]->value, STDOUT_FILENO);
        i++;
    }
}
*/
/*
void echo_command(t_exec_node *cmd)
{
    int	i = 0;
    int	flag = echo_flag(cmd, &i);

    if (cmd->tokens_argv[i])
        print_arguments(cmd, i);

    if (!flag)
        ft_putchar_fd('\n', STDOUT_FILENO);

    g_exit = 0;
}
*/
void echo_command(t_exec_node *cmd)
{
    int i;
    int flag;
	char *exit_code;

	i = 1;
	if (cmd->tokens_argv[1])
	{
		flag = echo_flag(cmd, i);
	}
	else
		flag = 0;
    // Verifica se há argumento= echo_flag(cmd, &i);
    if (cmd->tokens_argv[i])
    {
        // Expande variáveis como $? antes de imprimir
        while (cmd->tokens_argv[i] != NULL)
        {
            if (strcmp(cmd->tokens_argv[i]->value, "?") == 0)
            {
				exit_code = ft_itoa(g_exit);
                if (exit_code)
                {
                    ft_putstr_fd(exit_code, STDOUT_FILENO);
                    free(exit_code);
                }
            }
            else
            {
                ft_putstr_fd(cmd->tokens_argv[i]->value, STDOUT_FILENO);
            }
            if (cmd->tokens_argv[i + 1])
                ft_putchar_fd(' ', STDOUT_FILENO);
            i++;
        }
    }

    if (!flag)
        ft_putchar_fd('\n', STDOUT_FILENO);

    g_exit = 0;
}
