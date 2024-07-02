/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biltes <biltes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:55:48 by migupere          #+#    #+#             */
/*   Updated: 2024/07/02 16:47:12 by biltes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	ft_isnumber(char *str)
{
    int	i;

    i = 0;
    if (!str[i])
        return (false);
    if (str[i] == '+' || str[i] == '-')
        i++;
    while (str[i])
    {
        if (!ft_isdigit(str[i++]))
            return (false);
    }
    return (true);
}

static bool	islonglong(char *str)
{
    int	is_negative;
    int	len;

    if (*str == '-')
    {
        is_negative = 1;
        str++;
    }
    while (*str == '0' || *str == ' ')
        str++;
    if (!ft_isnumber(str))
        return (false);
    len = ft_strlen(str);
    if (len > 19)
        return (false);
    if (is_negative)
        return (ft_strncmp(str, "9223372036854775808", len) <= 0);
    else
        return (ft_strncmp(str, "9223372036854775807", len) <= 0);
}

void exit_command(t_shell *shell, t_exec_node *cmd) {
    if (cmd->tokens_argv[2]) {
        print_error(shell, cmd->tokens_argv[0]->value, "too many arguments", 1);
        return ; // Return early if there's an error
    }
    if (cmd->tokens_argv[1])
	{
        if (!islonglong(cmd->tokens_argv[1]->value) && ft_strcmp(cmd->tokens_argv[1]->value, "0")) {
            print_error(shell, cmd->tokens_argv[0]->value, ": numeric argument required", 2);
        } else
		{
            int exit_status = ft_atoi(cmd->tokens_argv[1]->value);
            g_exit = exit_status % 256;
        }
    }
    shell->status = STOP;
}
