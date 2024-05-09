/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migupere <migupere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:55:51 by migupere          #+#    #+#             */
/*   Updated: 2024/05/06 14:50:32 by migupere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_envp_sorted(t_shell *shell, int export)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = shell->env;
	while (i++ < shell->envp_size)
	{
		while (tmp)
		{
			if (tmp->index == i)
			{
				if (export && tmp->visible)
					ft_printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
				else if (export && !tmp->visible)
					ft_printf("declare -x %s\n", tmp->key);
				else if (!export && tmp->visible)
					ft_printf("%s=\"%s\"\n", tmp->key, tmp->value);
				break ;
			}
			tmp = tmp->next;
		}
		tmp = shell->env;
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

static bool	valid_args(char **argv)
{
	int		i;
	bool	flag;

	if (!argv[1])
		return (false);
	i = 0;
	flag = false;
	while (argv[++i])
	{
		if (*argv[i])
			flag = true;
	}
	return (flag);
}

static void	run_export(t_shell *shell, t_exec *cmd)
{
	int		i;
	char	*value;
	char	**split;

	if (!valid_args(cmd->argv))
		print_envp_sorted(shell, 1);
	else
	{
		i = 0;
		while (cmd->argv[++i])
		{
			if (!*cmd->argv[i] || !valid_var(shell, cmd->argv[i]))
				continue ;
			if (ft_strchr(cmd->argv[i], '='))
			{
				split = ft_split(cmd->argv[i], '=');
				value = ft_strdup(ft_strchr(cmd->argv[i], '=') + 1);
				env_export(shell, split[0], value, 1);
				free_array(split);
				free(value);
			}
			else
				env_export(shell, cmd->argv[i], "", 0);
		}
	}
}

void	export_command(t_shell *shell, t_exec *cmd)
{
	run_export(shell, cmd);
	if (shell->status == CONTINUE)
		g_exit = 0;
}