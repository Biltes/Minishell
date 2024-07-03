/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biltes <biltes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:49:37 by migupere          #+#    #+#             */
/*   Updated: 2024/07/03 17:48:23 by biltes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*manage_env_node(char *key, char *value, int visible, int action)
{
	t_env	*new;

	if (action == 0)
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (NULL);
		new->key = ft_strdup(key);
		new->value = ft_strdup(value);
		new->index = 0;
		new->visible = visible;
		new->next = NULL;
		return (new);
	}
	else if (action == 1)
	{
		free(key);
		if (value)
			free(value);
	}
	return (NULL);
}

void	envp_update(t_shell *shell)
{
	t_env	*tmp;
	int		i;

	tmp = shell->env;
	i = 0;
	if (shell->envp)
		free_array(shell->envp);
	shell->envp = malloc(sizeof(char *) * (shell->envp_size + 1));
	if (!shell->envp)
		return ;
	while (tmp)
	{
		if (tmp->visible)
		{
			shell->envp[i] = malloc(ft_strlen(tmp->key) \
				+ ft_strlen(tmp->value) + 2);
			if (!shell->envp[i])
				return ;
			strcpy(shell->envp[i], tmp->key);
			strcat(shell->envp[i], "=");
			strcat(shell->envp[i], tmp->value);
			i++;
		}
		tmp = tmp->next;
	}
	shell->envp[i] = NULL;
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

void	env_export(t_shell *shell, char *key, char *value, int visible)
{
	t_env	*tmp;
	bool	found;

	found = false;
	tmp = shell->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			found = true;
			if (visible)
			{
				free(tmp->value);
				tmp->value = ft_strdup(value);
				tmp->visible = visible;
			}
			break ;
		}
		tmp = tmp->next;
	}
	if (!found)
		shell->env = env_add_or_mod(shell, key, value, visible);
	envp_sort(shell);
	envp_update(shell);
}
