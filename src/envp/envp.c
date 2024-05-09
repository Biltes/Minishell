/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migupere <migupere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:44:14 by migupere          #+#    #+#             */
/*   Updated: 2024/05/06 16:35:28 by migupere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Prints the environment variables in the shell
void envp_print(t_shell *shell)
{
    t_env *tmp;

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

// Sets the index of each environment variable in the shell to 0
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

// Updates the environment variables in the shell
void	envp_update(t_shell *shell)
{
    t_env	*tmp;
    char	*env;
    int		i;

    // Free the existing environment variables if they exist
    if (shell->envp)
        free_array(shell->envp);

    // If there are no environment variables, set envp to NULL and return
    if (!shell->env)
    {
        shell->envp = NULL;
        return ;
    }

    // Allocate memory for the new environment variables
    shell->envp = ft_calloc(shell->envp_size + 1, sizeof(char *));

    tmp = shell->env;
    i = 0;
    // Copy each environment variable into the newly allocated memory
    while (tmp)
    {
        if (tmp->visible)
        {
            env = ft_strjoin(tmp->key, "=");
            shell->envp[i++] = ft_strjoin(env, tmp->value);
            free(env);
        }
        tmp = tmp->next;
    }
}


// Sorts the environment variables in the shell
void	envp_sort(t_shell *shell)
{
    t_env	*tmp;
    t_env	*max;
    char	*max_key;
    int		i;

    // Set the index of each environment variable to 0
    zero_index(shell);

    i = shell->envp_size;
    while (i--)
    {
        tmp = shell->env;
        max = NULL;
        max_key = "";
        // Find the maximum key that hasn't been indexed yet
        while (tmp)
        {
            if (ft_strcmp(tmp->key, max_key) > 0 && tmp->index == 0)
            {
                max = tmp;
                max_key = tmp->key;
            }
            tmp = tmp->next;
        }
        // Set the index of the maximum key to i + 1
        if (max)
            max->index = i + 1;
    }
}

// Converts the environment variables from an array to a linked list
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
            free (value);
        i++;
    }
    // Sort the environment variables
    envp_sort(shell);
}