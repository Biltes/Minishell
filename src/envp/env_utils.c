/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:49:37 by migupere          #+#    #+#             */
/*   Updated: 2024/07/04 15:23:48 by pevieira         ###   ########.fr       */
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

static size_t	envp_update_size(t_shell *shell)
{
	t_env	*tmp;
	size_t	total_size;

	tmp = shell->env;
	total_size = 0;
	while (tmp)
	{
		if (tmp->visible)
			total_size += strlcpy(NULL, tmp->key, 0) \
				+ strlcpy(NULL, tmp->value, 0) + 2;
		tmp = tmp->next;
	}
	return (total_size + 1);
}

static void	envp_update_copy(t_shell *shell, size_t envp_size, int i)
{
	t_env	*tmp;
	size_t	key_len;
	size_t	value_len;

	tmp = shell->env;
	shell->envp = malloc(sizeof(char *) * envp_size);
	if (!shell->envp)
		return ;
	while (tmp)
	{
		if (tmp->visible)
		{
			key_len = strlcpy(NULL, tmp->key, 0);
			value_len = strlcpy(NULL, tmp->value, 0);
			shell->envp[i] = malloc(key_len + value_len + 2);
			if (!shell->envp[i])
				return ;
			ft_strlcpy(shell->envp[i], tmp->key, key_len + 1);
			ft_strlcat(shell->envp[i], "=", key_len + 2);
			ft_strlcat(shell->envp[i], tmp->value, key_len + value_len + 2);
			i++;
		}
		tmp = tmp->next;
	}
	shell->envp[i] = NULL;
}

void	envp_update(t_shell *shell)
{
	size_t	envp_size;

	if (shell->envp)
		free_array(shell->envp);
	envp_size = envp_update_size(shell);
	shell->envp = NULL;
	if (envp_size > 0)
		envp_update_copy(shell, envp_size, 0);
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
	new = manage_env_node(key, value, visible, 0);
	if (!new)
		return (NULL);
	shell->envp_size++;
	if (!shell->env)
		shell->env = new;
	else
	{
		tmp = shell->env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	envp_update(shell);
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
