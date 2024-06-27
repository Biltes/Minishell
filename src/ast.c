/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:04:48 by pevieira          #+#    #+#             */
/*   Updated: 2024/06/27 16:30:28 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_cmd	*init_heredoc_cmd(t_cmd *cmd, t_token *token)
{
	t_here	*here;
	t_cmd	*tmp;
	t_cmd	*tmp2;

	here = (t_here *)ft_calloc(1, sizeof(t_here));
	here->type = HERE_DOC;
	here->eof = ft_strdup((char *)token->value);
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
/*ANTIGO
static t_cmd	*check_redirections(t_cmd *cmd, t_shell *m_shell)
{
	int	red_type;

	while (check_presence(m_shell->lexer, "<>", 1) || \
		check_presence(m_shell->lexer, "<>", 2))
	{
		red_type = m_shell->next_token->type;
		m_shell->next_token = lexer_get_next_token(m_shell->lexer);
		if (red_type == TOKEN_REDIR1)
			cmd = init_redir_cmd(cmd, m_shell->next_token, O_RDONLY, 0);
		else if (red_type == TOKEN_REDIR2)
			cmd = init_redir_cmd(cmd, m_shell->next_token, \
				O_WRONLY | O_CREAT | O_TRUNC, 1);
		else if (red_type == TOKEN_REDIR3)
			cmd = init_redir_cmd(cmd, m_shell->next_token, \
				O_WRONLY | O_CREAT | O_APPEND, 1);
		else if (red_type == TOKEN_REDIR4) //TALVEZ COLOCAR VERIRICAÇÃO AQUI m_shell->next_token->type == ID)
			cmd = init_heredoc_cmd(cmd, m_shell->next_token);
	}
	return (cmd);
}*/

static t_cmd	*check_redirections(t_cmd *cmd, t_shell *m_shell)
{
	int	red_type;

	while (check_presence(m_shell->lexer, "<>", 1) || \
		check_presence(m_shell->lexer, "<>", 2))
	{
		red_type = m_shell->next_token->type; //o erro comeca aqui
		m_shell->next_token = lexer_get_next_token(m_shell->lexer, m_shell);
		if (m_shell->next_token->type != TOKEN_ID)
		{
			printf("minishell: syntax error near unexpected token `%i '\n", red_type);//TALVEZ ARRANJAR AQUI??para o tipo de erro
			exit_error("", m_shell); //TALVEZ ARRANJAR AQUI??para o tipo de erro
			return (NULL);
		}
		else if (red_type == TOKEN_REDIR1)
			cmd = init_redir_cmd(cmd, m_shell->next_token, O_RDONLY, 0);
		else if (red_type == TOKEN_REDIR2)
			cmd = init_redir_cmd(cmd, m_shell->next_token, \
				O_WRONLY | O_CREAT | O_TRUNC, 1);
		else if (red_type == TOKEN_REDIR3)
			cmd = init_redir_cmd(cmd, m_shell->next_token, \
				O_WRONLY | O_CREAT | O_APPEND, 1);
		else if (red_type == TOKEN_REDIR4)
			cmd = init_heredoc_cmd(cmd, m_shell->next_token);
	}
	return (cmd);
}

void	ft_add_token_to_exec(t_exec_node *exec, t_token *token)
{
	int	i;

	i = 0;
	if (!token)
		return ;
	printf("o valor do token é: %s\n", token->value);
	while (exec->tokens_argv[i] && i < MAXARG)
		i++;
	if (!exec->tokens_argv[i])
		exec->tokens_argv[i] = token;
}
static char *strjoin_with_space(const char *s1, const char *s2)
{
    char *result;
    size_t len1 = ft_strlen(s1);
    size_t len2 = ft_strlen(s2);

    result = (char *)malloc(len1 + len2 + 2); // +2 para o espaço e o terminador nulo
    if (!result)
        return (NULL);

    ft_strlcpy(result, s1, len1 + 1);   // Copia s1 para result
    result[len1] = ' ';              // Adiciona o espaço
    ft_strlcpy(result + len1 + 1, s2, len2 + 1); // Copia s2 para result após o espaço

    return result;
}


static void	ft_add_file_to_redir(t_redir_node *redir, t_token *token)
{
	char *new_file;

	new_file = strjoin_with_space(redir->file, token->value);
    free(redir->file); // Libera a memória anterior
    redir->file = new_file;

}

static t_cmd	*parsing_exec(t_shell *m_shell)
{
	t_cmd	*ret;

	if (check_presence(m_shell->lexer, "(", 1))
	{
		exit_error("this is not the bonus", m_shell);
		return (NULL);
	}
	ret = init_exec_node();
	ret = check_redirections(ret, m_shell);
	while (!check_presence(m_shell->lexer, "|", 1))
	{
		if (!m_shell->next_token)
			break ;
		if (m_shell->next_token->type != TOKEN_ID)
		{
			exit_error("Erro syntax2\n", m_shell);
			return (ret);
		}
		printf("ret type: %d\n", ret->type);
		if (ret->type != 2)
			ft_add_token_to_exec((t_exec_node *) ret, m_shell->next_token);
		else if (ret->type == 2)
			ft_add_file_to_redir((t_redir_node *)ret, m_shell->next_token);
		m_shell->next_token = lexer_get_next_token(m_shell->lexer, m_shell);
		ret = check_redirections(ret, m_shell);
	}
	return (ret);
}


t_cmd	*parsing_exec_and_pipe(t_shell *m_shell)
{
	t_cmd	*cmd;

	m_shell->next_token = lexer_get_next_token(m_shell->lexer, m_shell);
	if (check_presence(m_shell->lexer, "|", 1) \
		&& m_shell->status == CONTINUE)
	{
		exit_error("this is not the bonus!", m_shell);
		return (NULL);
	}
	cmd = parsing_exec(m_shell);
	if (cmd && check_presence(m_shell->lexer, "|", 1))
	{
		free(m_shell->next_token);
		cmd = init_pipe_node(cmd, parsing_exec_and_pipe(m_shell));
	}
	return (cmd);
}
