/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:49:06 by migupere          #+#    #+#             */
/*   Updated: 2024/07/20 11:17:14 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_contains_only(char *str, char *characters)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_strchr(characters, str[i]))
			return (0);
	return (i);
}

static int	echo_flag(t_exec_node *cmd, int *arg_index)
{
	int	index;
	int	flag;

	flag = 0;
	index = *arg_index;
	while (cmd->tokens_argv[index] && cmd->tokens_argv[index]->value[0] == '-')
	{
		if (ft_contains_only(&cmd->tokens_argv[index]->value[1], "n"))
		{
			flag = 1;
			index++;
		}
		else
			break ;
	}
	*arg_index = index;
	return (flag);
}

void	echo_command(t_exec_node *cmd)
{
	int	i;
	int	flag;

	i = 1;
	if (cmd->tokens_argv[1])
	{
		flag = echo_flag(cmd, &i);
	}
	else
		flag = 0;
	if (cmd->tokens_argv[i])
	{
		while (cmd->tokens_argv[i] != NULL)
		{
			ft_putstr_fd(cmd->tokens_argv[i]->value, STDOUT_FILENO);
			if (cmd->tokens_argv[i + 1])
				ft_putchar_fd(' ', STDOUT_FILENO);
			i++;
		}
	}
	if (!flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	g_exit = 0;
}
