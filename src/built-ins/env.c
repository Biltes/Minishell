/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:49:11 by migupere          #+#    #+#             */
/*   Updated: 2024/07/20 11:17:40 by pevieira         ###   ########.fr       */
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

bool	env_rm(char *key, t_shell *shell)
{
	t_env	*tmp;
	t_env	*tmp_last;

	tmp = shell->env;
	tmp_last = tmp;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			tmp_last->next = tmp->next;
			if (tmp == shell->env)
				shell->env = tmp->next;
			manage_env_node(tmp->key, tmp->value, tmp->visible, 1);
			free(tmp);
			shell->envp_size--;
			envp_update(shell);
			return (true);
		}
		tmp_last = tmp;
		tmp = tmp->next;
	}
	return (false);
}

t_env	*env_add_or_mod(t_shell *shell, char *key, char *value, int visible)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			tmp->visible = visible;
			envp_update(shell);
			return (shell->env);
		}
		tmp = tmp->next;
	}
	env_add(shell, key, value, visible);
	return (shell->env);
}
