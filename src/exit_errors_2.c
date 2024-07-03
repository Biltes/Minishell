/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_errors_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:35:36 by pevieira          #+#    #+#             */
/*   Updated: 2024/07/03 14:47:40 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_exec_node(t_exec_node *exec)
{
	int		i;
	t_token	*tokenzinho;

	i = 0;
	if (!exec)
		return ;
	tokenzinho = exec->tokens_argv[i];
	while (tokenzinho)
	{
		free(tokenzinho->value);
		free(tokenzinho);
		i++;
		tokenzinho = exec->tokens_argv[i];
	}
	free(exec);
	exec = NULL;
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	envp_destroy(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	clean_exit(t_shell *m_shell, int mode)
{
	if (m_shell->input)
	{
		free(m_shell->input);
		m_shell->input = NULL;
	}
	if (m_shell->ast)
		free_cmd(m_shell->ast);
	if (m_shell->prompt)
		free(m_shell->prompt);
	if (m_shell->lexer)
		free(m_shell->lexer);
	if (m_shell->next_token)
		free(m_shell->next_token);
	if (m_shell->env)
		envp_destroy(m_shell->env);
	if (m_shell->envp)
		free_array(m_shell->envp);
	(void) mode;
}
