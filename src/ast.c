/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:04:48 by pevieira          #+#    #+#             */
/*   Updated: 2024/07/15 21:52:02 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_cmd	*init_heredoc_cmd(t_cmd *cmd, t_token *token, t_here *here)
{
	t_cmd	*tmp;
	t_cmd	*tmp2;

	here = (t_here *)ft_calloc(1, sizeof(t_here));
	here->type = HERE_DOC;
	here->eof = ft_strdup((char *)token->value);
	free(token->value);
	here->mode = O_WRONLY | O_CREAT | O_TRUNC;
	here->fdin = dup(STDIN_FILENO);
	here->fdout = dup(STDOUT_FILENO);
	if (cmd->type == EXEC || cmd->type == REDIR)
		here->cmd = cmd;
	else
	{
		tmp = cmd;
		while (tmp->type != EXEC && tmp->type != REDIR)
		{
			tmp2 = tmp;
			tmp = ((t_redir_node *)tmp)->cmd;
		}
		((t_redir_node *)tmp2)->cmd = (t_cmd *)here;
		here->cmd = tmp;
		return (cmd);
	}
	return ((t_cmd *)here);
}

static t_cmd	*error_red(t_cmd *cmd, t_shell *m_shell, int red_type)
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

static t_cmd	*check_redirections(t_cmd *cmd, t_shell *m_shell, int red_type)
{
	while (scan(m_shell->lexer, "<>", 1) || scan(m_shell->lexer, "<>", 2))
	{
		red_type = m_shell->next_token->type;
		free(m_shell->next_token);
		if (red_type == TOKEN_REDIR4)
			m_shell->heredoc = 1;
		m_shell->next_token = lexer_get_next_token(m_shell->lexer, m_shell);
		if (m_shell->next_token->type != TOKEN_ID)
			return (error_red(cmd, m_shell, m_shell->next_token->type));
		else if (red_type == TOKEN_REDIR1)
			cmd = init_redir_cmd(cmd, m_shell->next_token, O_RDONLY, 0);
		else if (red_type == TOKEN_REDIR2)
			cmd = init_redir_cmd(cmd, m_shell->next_token, \
				O_WRONLY | O_CREAT | O_TRUNC, 1);
		else if (red_type == TOKEN_REDIR3)
			cmd = init_redir_cmd(cmd, m_shell->next_token, \
				O_WRONLY | O_CREAT | O_APPEND, 1);
		else if (red_type == TOKEN_REDIR4)
			cmd = init_heredoc_cmd(cmd, m_shell->next_token, NULL);
		free(m_shell->next_token);
		m_shell->heredoc = 0;
		m_shell->next_token = lexer_get_next_token(m_shell->lexer, m_shell);
	}
	return (cmd);
}

void	ft_add_token_to_exec(t_exec_node *exec, t_token *token)
{
	int	i;

	i = 0;
	if (!token)
		return ;
	if (ft_strcmp(token->value, "") == 0)
	{
		if (token->value)
			free(token->value);
		free (token);
		return ;
	}
	while (exec->tokens_argv[i] && i < MAXARG)
		i++;
	if (!exec->tokens_argv[i] && i < MAXARG)
		exec->tokens_argv[i] = token;
}

static t_cmd	*parsing_exec(t_shell *m_shell)
{
	t_cmd		*ret;
	t_exec_node	*cmd;

	if (scan(m_shell->lexer, "(", 1))
	{
		exit_error("no support for `('\n", m_shell, NULL);
		m_shell->status = RESTORE;
		free(m_shell->next_token->value);
		free(m_shell->next_token);
		return (NULL);
	}
	ret = init_exec_node();
	cmd = (t_exec_node *) ret;
	ret = check_redirections(ret, m_shell, 0);
	while (!scan(m_shell->lexer, "|", 1) && m_shell->status == CONTINUE)
	{
		if (!m_shell->next_token)
			break ;
		if (m_shell->next_token->type != TOKEN_ID)
			break ;
		ft_add_token_to_exec((t_exec_node *) cmd, m_shell->next_token);
		m_shell->next_token = lexer_get_next_token(m_shell->lexer, m_shell);
		ret = check_redirections(ret, m_shell, 0);
	}
	return (ret);
}

t_cmd	*parsing_exec_and_pipe(t_shell *m_shell)
{
	t_cmd	*cmd;

	m_shell->next_token = lexer_get_next_token(m_shell->lexer, m_shell);
	if (scan(m_shell->lexer, "|", 1)
		&& m_shell->status == CONTINUE)
	{
		exit_error("syntax error near unexpected token ", m_shell, "|");
		free(m_shell->next_token);
		m_shell->status = RESTORE;
		return (NULL);
	}
	cmd = parsing_exec(m_shell);
	if (cmd && scan(m_shell->lexer, "|", 1))
	{
		free(m_shell->next_token);
		cmd = init_pipe_node(cmd, parsing_exec_and_pipe(m_shell));
	}
	return (cmd);
}
