/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migupere <migupere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:16:48 by pevieira          #+#    #+#             */
/*   Updated: 2024/05/29 18:06:29 by migupere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
static void	execute_node(t_redir_node *redir)
{
	if (!redir)execute_exec
		return ;
	execute_cmd(redir->cmd);
}

static void	free_here_doc(t_here *here)
{
	if (!here)
		return ;
	execute_cmd(here->cmd);
	if (here->eof)
		free(here->eof);
}

static void	execute_pipe(t_pipe_node *pipe)
{
	if (!pipe)
		return ;
	execute_cmd(pipe->left);
	execute_cmd(pipe->right);
}
void	executor(t_shell *m_shell)
{
	if (m_shell->ast->type == PIPE)
		printf("hello");
	usleep(1000);
	if (m_shell->ast)
		execute_cmd(m_shell->ast);
}

void	execute_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	else if (cmd->type == PIPE)
		execute_pipe((t_pipe_node *)cmd);
	else if (cmd->type == HERE_DOC)
		execute_here_doc((t_here *)cmd);
	else if (cmd->type == REDIR)
		execute_node((t_redir_node *)cmd);
	else if (cmd->type == EXEC)
		execute_exec((t_exec_node *)cmd);
}
*/

void executor(t_shell *m_shell)
{
    if (m_shell->ast)
	{
        run_cmd(m_shell, m_shell->ast);
    }
}
