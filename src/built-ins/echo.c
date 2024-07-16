/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:49:06 by migupere          #+#    #+#             */
/*   Updated: 2024/07/16 15:42:47 by pevieira         ###   ########.fr       */
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

static void	print_exit_code(void)
{
	char	*exit_code;

	exit_code = ft_itoa(g_exit);
	if (exit_code)
	{
		ft_putstr_fd(exit_code, STDOUT_FILENO);
		free(exit_code);
	}
}

static void	print_token_value(t_exec_node *cmd, int *i)
{
	if (strcmp(cmd->tokens_argv[*i]->value, "?") == 0)
	{
		//printf("AAAAA\n");
		print_exit_code();
	}
	else
	{
		ft_putstr_fd(cmd->tokens_argv[*i]->value, STDOUT_FILENO);
	}
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
			print_token_value(cmd, &i);
			if (cmd->tokens_argv[i + 1])
				ft_putchar_fd(' ', STDOUT_FILENO);
			i++;
		}
	}
	if (!flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	g_exit = 0;
}
