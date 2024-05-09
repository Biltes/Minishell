/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migupere <migupere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:55:48 by migupere          #+#    #+#             */
/*   Updated: 2024/05/06 14:49:56 by migupere         ###   ########.fr       */
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

void	exit_command(t_shell *shell, t_exec *cmd)
{
    if (cmd->argv[2])
        print_error(shell, cmd->argv[0], "too many arguments", 2);
    if (cmd->argv[1])
    {
        if (!islonglong(cmd->argv[1]) && ft_strcmp(cmd->argv[1], "0"))
        {
            print_error(shell, cmd->argv[0], cmd->argv[1], 2);
            print_error(shell, cmd->argv[0], ": numeric argument required", 2);
        }
        else
        {
            int exit_status = ft_atoi(cmd->argv[1]);
            if (exit_status > 255)
            {
                print_error(shell, cmd->argv[0], "exit status greater than 255, it will be modulo 256", 2);
            }
            g_exit = exit_status % 256;
        }
    }
    shell->status = STOP;
}
