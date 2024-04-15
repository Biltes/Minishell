/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:38:14 by pevieira          #+#    #+#             */
/*   Updated: 2024/04/15 17:53:32 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int exit_error(char *str, t_shell *m_shell)
{
    printf("%s",str);
    clean_exit(m_shell, EXIT_SUCCESS);
    return (1);
}


void	free_exec_node(t_exec_node *exec)
{
    int i;
    t_token *tokenzinho;

    i = 0;
	if (!exec)
		return ;
    tokenzinho = exec->tokens_argv[i];
	while (tokenzinho)
	{
		printf("o executavel->  %s.\n\n\n", exec->tokens_argv[i]->value);
        free(tokenzinho->value);
        free(tokenzinho);
        i++;
        tokenzinho = exec->tokens_argv[i];
    }
	free(exec);
	printf("LIMPANDO UM EXEC\n");
	exec = NULL;
}

static void	free_redir_node(t_redir_node *redir)
{
	if (!redir)
		return ;
	free_cmd(redir->cmd);
	if (redir->file)
		free(redir->file);
	free(redir);
	printf("LIMPANDO A ESTRUTURA DO REDIR\n");
	redir = NULL;
}


static void	free_here_doc(t_here *here)
{
	if (!here)
		return ;
	free_cmd(here->cmd);
	if (here->eof)
		free(here->eof);
	free(here);
	here = NULL;
	printf("LIMPANDO A ESTRUTURA DO HEREDOC\n");
}

static void	free_pipe_node(t_pipe_node *pipe)
{
	if (!pipe)
		return ;
	free_cmd(pipe->left);
	free_cmd(pipe->right);
	free(pipe);
	printf("LIMPANDO A ESTRUTURA DO PIPE\n");
	pipe = NULL;
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	else if (cmd->type == PIPE)
		free_pipe_node((t_pipe_node *)cmd);
	else if (cmd->type == HERE_DOC)
		free_here_doc((t_here *)cmd);
	else if (cmd->type == REDIR)
		free_redir_node((t_redir_node *)cmd);
	else if (cmd->type == EXEC)
		free_exec_node((t_exec_node *)cmd);
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
		printf("input liberado\n");
	}
	if (m_shell->ast)
		free_cmd(m_shell->ast);
    if (m_shell->prompt)
		free(m_shell->prompt);
    if (m_shell->lexer)
	{
        free(m_shell->lexer);
	}
	if (m_shell->next_token)
	{
		free(m_shell->next_token);
	}
	if (m_shell->env)
		envp_destroy(*m_shell->env);
	if (m_shell->envp)
		free_array(m_shell->envp);    
	if (mode == BUILTIN_EXIT)
		exit(EXIT_SUCCESS);
	else
		exit(g_exit);
}

