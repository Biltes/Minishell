/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biltes <biltes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:47:47 by migupere          #+#    #+#             */
/*   Updated: 2024/05/31 18:42:33 by biltes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
t_env	*manage_env_node(char *key, char *value, int visible, int action)
{
    t_env	*new;

    if (action == 0) // 0 for create
    {
		printf("A7\n");
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
		printf("A93\n");
        free(key);
        if (value)
            free(value);
    }
	printf("A222\n");
    return NULL;
}*/
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
void envp_update(t_shell *shell)
{
    t_env *tmp;
    int i;

    // Free the old envp if it exists
    if (shell->envp)
    {
        i = 0;
        while (shell->envp[i])
        {
            free(shell->envp[i]);
            i++;
        }
        free(shell->envp);
    }

    // Allocate memory for the new envp
    shell->envp = malloc(sizeof(char *) * (shell->envp_size + 1));
    if (!shell->envp)
        return;

    // Populate the envp array
    tmp = shell->env;
    i = 0;
    while (tmp)
    {
        if (tmp->visible)
        {
            shell->envp[i] = malloc(ft_strlen(tmp->key) + ft_strlen(tmp->value) + 2);
            if (!shell->envp[i])
                return;
            ft_strlcpy(shell->envp[i], tmp->key, ft_strlen(tmp->key) + 1);
            ft_strlcat(shell->envp[i], "=", ft_strlen(tmp->key) + 2);
            ft_strlcat(shell->envp[i], tmp->value, ft_strlen(tmp->key) + ft_strlen(tmp->value) + 2);
            //printf("envp[%d]: %s\n", i, shell->envp[i]); // Ponto de depuração
            i++;
        }
        tmp = tmp->next;
    }
    shell->envp[i] = NULL;
    //printf("Updated envp with %d entries.\n", i); // Ponto de depuração
}



/*
t_env	*env_add_or_mod(t_shell *shell, char *key, char *value, int visible)
{
    t_env	*tmp;

	printf("A2212122\n");
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
	printf("A2\n");
    new = manage_env_node(key, value, visible, 0);
	printf("A3\n");
    if (!new)
		return (NULL);
	printf("A1\n");
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
}*/
t_env *env_add_or_mod(t_shell *shell, char *key, char *value, int visible)
{
    t_env *tmp;

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

    t_env *new;
    new = manage_env_node(key, value, visible, 0);
    if (!new)
        return (NULL);

    shell->envp_size++;
    if (!shell->env)
    {
        shell->env = new;
    }
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


bool env_rm(char *key, t_shell *shell)
{
    t_env *tmp;
    t_env *tmp_last;

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

void env_export(t_shell *shell, char *key, char *value, int visible)
{
    t_env *tmp;
    bool found = false;

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
    envp_update(shell);
}

/*
char	*env_get(char *key, t_shell *shell)
{
	printf("ola\n");
    t_env	*tmp;

    tmp = shell->env;
    while (tmp)
    {
		printf("o env key é: %s\n", tmp->key);
		printf("o env value é: %s\n", tmp->value);
		printf("o env int é: %d\n", tmp->visible);
		printf("o env index é: %d\n", tmp->index);
        if (!ft_strcmp(tmp->key, key))
            return (tmp->value);
        tmp = tmp->next;
    }
    return (NULL);
}*/

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
