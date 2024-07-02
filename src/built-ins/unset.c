/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biltes <biltes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:55:57 by migupere          #+#    #+#             */
/*   Updated: 2024/07/02 20:08:53 by biltes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	valid_unset_var(t_shell *shell, char *arg)
{
	int		i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (error_in(shell, "unset: ", arg, 1));
	while (arg[++i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (error_in(shell, "unset: ", arg, 1));
	}
	return (true);
}


int get_key_and_rm(char *key, t_shell *shell) {
    t_env *tmp;
    t_env *prev;

    tmp = (shell->env);
    prev = NULL;
    while (tmp) {
        if (strcmp(tmp->key, key) == 0) {
            if (prev)
                prev->next = tmp->next;
            else
                (shell->env) = tmp->next;
            free(tmp->key);
            free(tmp->value);
            free(tmp);
            return 1;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    return (0);
}

void unset_command(t_shell *shell, t_exec_node *cmd)
{
    int i;

    i = 0;
    while (cmd->tokens_argv[++i])
    {
        if (*cmd->tokens_argv[i]->value && valid_unset_var(shell, cmd->tokens_argv[i]->value))
        {
            if (!get_key_and_rm(cmd->tokens_argv[i]->value, shell))
                return ;
        }
    }
    if (shell->status == CONTINUE)
        g_exit = 0;
}
