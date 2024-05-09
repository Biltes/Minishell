/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migupere <migupere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:47:47 by migupere          #+#    #+#             */
/*   Updated: 2024/05/06 16:29:48 by migupere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*manage_env_node(char *key, char *value, int visible, int action)
{
    t_env	*new;

    if (action == 0) // 0 for create
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
    else if (action == 1) // 1 for free
    {
        free(key);
        if (value)
            free(value);
    }
    return NULL;
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

    // If we reach here, it means the key was not found, so we add a new node
    t_env	*new;

    new = manage_env_node(key, value, visible, 0);
    if (!new)
        return (NULL);
    shell->envp_size++;
    if (!shell->env)
        return (new);
    tmp = shell->env;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    envp_sort(shell);
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
            envp_sort(shell);
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
    bool	found = false;

    tmp = shell->env;
    while (tmp)
    {
        if (!ft_strcmp(tmp->key, key))
        {
            found = true;
            if (visible)
                env_add_or_mod(shell, key, value, visible);
            break;
        }
        tmp = tmp->next;
    }

    if (!found)
        env_add_or_mod(shell, key, value, visible);
}

char	*env_get(char *key, t_shell *shell)
{
    t_env	*tmp;

    tmp = shell->env;
    while (tmp)
    {
        if (!ft_strcmp(tmp->key, key))
            return (tmp->value);
        tmp = tmp->next;
    }
    return (NULL);
}