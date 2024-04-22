/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:30:45 by pevieira          #+#    #+#             */
/*   Updated: 2024/04/22 11:02:09 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_cmd	*init_exec_node(void)
{
	t_exec_node	*cmd;

	cmd = (t_exec_node *)ft_calloc(1, sizeof(t_exec_node));
	cmd->type = EXEC;
	return ((t_cmd *)cmd);
}

t_cmd	*init_pipe_node(t_cmd *left, t_cmd *right)
{
	t_pipe_node	*cmd;

	cmd = (t_pipe_node *)ft_calloc(1, sizeof(t_pipe_node));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*init_redir_cmd(t_cmd *cmd, t_token *token, int mode, int fd)
{
	t_redir_node	*redir;
	t_cmd			*tmp;
	t_cmd			*tmp2;

	redir = (t_redir_node *)ft_calloc(1, sizeof(t_redir_node));
	redir->type = REDIR;
	redir->file = ft_strdup(token->value);
	redir->mode = mode;
	redir->fd = fd;
	if (cmd->type == EXEC)
		redir->cmd = cmd;
	else
	{
		tmp = cmd;
		while (tmp->type != EXEC)
		{
			tmp2 = tmp;
			tmp = ((t_redir_node *)tmp)->cmd;
		}
		((t_redir_node *)tmp2)->cmd = (t_cmd *)redir;
		redir->cmd = tmp;
		return (cmd);
	}
	return ((t_cmd *)redir);
}
