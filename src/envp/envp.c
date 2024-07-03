/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:49:40 by migupere          #+#    #+#             */
/*   Updated: 2024/07/03 15:08:27 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	envp_print(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (tmp->visible)
		{
			ft_putstr_fd(tmp->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd(tmp->value, STDOUT_FILENO);
		}
		tmp = tmp->next;
	}
}

static void	zero_index(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		tmp->index = 0;
		tmp = tmp->next;
	}
}

void	envp_sort(t_shell *shell)
{
	t_env	*tmp;
	t_env	*max;
	char	*max_key;
	int		i;

	zero_index(shell);
	i = shell->envp_size;
	while (i--)
	{
		tmp = shell->env;
		max = NULL;
		max_key = "";
		while (tmp)
		{
			if (ft_strcmp(tmp->key, max_key) > 0 && tmp->index == 0)
			{
				max = tmp;
				max_key = tmp->key;
			}
			tmp = tmp->next;
		}
		if (max)
			max->index = i + 1;
	}
}

void	envp_to_list(char **envp, t_shell *shell)
{
	int		i;
	char	**split;
	char	*value;

	shell->env = NULL;
	i = 0;
	while (envp[i])
	{
		split = ft_split(envp[i], '=');
		if (ft_strchr(envp[i], '='))
			value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		else
			value = NULL;
		if (split && split[0])
			shell->env = env_add_or_mod(shell, split[0], value, 1);
		free_array(split);
		if (value)
			free(value);
		i++;
	}
	envp_sort(shell);
	envp_update(shell);
}
