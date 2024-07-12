/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:38:14 by pevieira          #+#    #+#             */
/*   Updated: 2024/07/12 11:18:59 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exit_error(char *str, t_shell *m_shell, char *char_error)
{
	if (char_error != NULL)
	{
		printf("minishell: ");
		printf ("%s", str);
		printf("`%c'\n", char_error[0]);
	}
	else
	{
		printf("minishell: ");
		printf ("%s", str);
	}
	(void)m_shell;
	return (1);
}

static void	free_redir_node(t_redir_node *redir)
{
	if (!redir)
		return ;
	if (redir->cmd)
	{
		free_cmd(redir->cmd);
		redir->cmd = NULL;
	}
	if (redir->file)
	{
		free(redir->file);
		redir->file = NULL;
	}
	free(redir);
	redir = NULL;
}

static void	free_here_doc(t_here *here)
{
	if (!here)
		return ;
	if (here->cmd)
		free_cmd(here->cmd);
	if (here->eof)
		free(here->eof);
	free(here);
	here = NULL;
}

static void	free_pipe_node(t_pipe_node *pipe)
{
	if (!pipe)
		return ;
	free_cmd(pipe->left);
	free_cmd(pipe->right);
	free(pipe);
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
