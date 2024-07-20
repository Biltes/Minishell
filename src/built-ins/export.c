/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:49:26 by migupere          #+#    #+#             */
/*   Updated: 2024/07/20 11:17:51 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_envp_sorted(t_shell *shell, int export, int i)
{
	t_env		*tmp;

	while (++i <= shell->envp_size)
	{
		tmp = shell->env;
		while (tmp)
		{
			if (tmp->index == i)
			{
				if (export)
				{
					if (tmp->visible)
						ft_printf("declare-x %s=\"%s\"\n", \
							tmp->key, tmp->value);
					else
						ft_printf("declare-x %s\n", tmp->key);
				}
				else if (tmp->visible)
					ft_printf("%s=\"%s\"\n", tmp->key, tmp->value);
				break ;
			}
			tmp = tmp->next;
		}
	}
}

static bool	valid_var(t_shell *shell, char *arg)
{
	int		i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (error_in(shell, "export: ", arg, 1));
	while (arg[++i])
	{
		if (arg[i] == '=')
			break ;
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (error_in(shell, "export: ", arg, 1));
	}
	return (true);
}

static bool	valid_args(t_token **tokens_argv)
{
	int		i;
	bool	flag;

	if (!tokens_argv[1])
		return (false);
	i = 0;
	flag = false;
	while (tokens_argv[++i])
	{
		if (*tokens_argv[i]->value)
			flag = true;
	}
	return (flag);
}

static void	run_export(t_shell *shell, t_exec_node *cmd, int i)
{
	char	*value;
	char	**split;

	if (!valid_args(cmd->tokens_argv))
		print_envp_sorted(shell, 1, 1);
	else
	{
		while (cmd->tokens_argv[++i])
		{
			if (!*cmd->tokens_argv[i]->value || \
				!valid_var(shell, cmd->tokens_argv[i]->value))
				continue ;
			if (ft_strchr(cmd->tokens_argv[i]->value, '='))
			{
				split = ft_split(cmd->tokens_argv[i]->value, '=');
				value = ft_strdup(ft_strchr(cmd->tokens_argv[i]->value, '=') \
					+ 1);
				env_export(shell, split[0], value, 1);
				free_array(split);
				free(value);
			}
			else
				env_export(shell, cmd->tokens_argv[i]->value, "", 0);
		}
	}
}

void	export_command(t_shell *shell, t_exec_node *cmd)
{
	run_export(shell, cmd, 0);
}
