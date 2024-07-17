/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_errors_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:35:36 by pevieira          #+#    #+#             */
/*   Updated: 2024/07/17 10:02:18 by pevieira         ###   ########.fr       */
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
	while (array && array[i])
		free(array[i++]);
	free(array);
}

void	clean_envp(t_env *env)
{
	t_env	*next_env;

	while (env)
	{
		next_env = env->next;
		free(env->value);
		free(env->key);
		free(env);
		env = next_env;
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
		clean_envp(m_shell->env);
	if (m_shell->envp)
		free_array(m_shell->envp);
	(void) mode;
}

t_cmd	*error_red(t_cmd *cmd, t_shell *m_shell, int red_type)
{
	if (red_type == TOKEN_REDIR1)
		exit_error("syntax error near token ´<'\n", m_shell, NULL);
	else if (red_type == TOKEN_REDIR2)
		exit_error("syntax error near token ´>'\n", m_shell, NULL);
	else if (red_type == TOKEN_REDIR3)
		exit_error("syntax error near token ´>>'\n", m_shell, NULL);
	else if (red_type == TOKEN_PIPE)
		exit_error("syntax error near token ´|'\n", m_shell, NULL);
	else
		exit_error("syntax error near token ´newline'\n", m_shell, NULL);
	return (cmd);
}

