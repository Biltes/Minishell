/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:41:54 by pevieira          #+#    #+#             */
/*   Updated: 2024/07/13 13:57:02 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*init_token(int type, char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(struct s_token));
	token->type = type;
	token->value = value;
	return (token);
}

int	init_ast(t_shell *m_shell)
{
	t_cmd	*cmd;

	cmd = parsing_exec_and_pipe(m_shell);
	if (scan(m_shell->lexer, "&", 2) && cmd)
	{
		exit_error("no support for `&&'\n", m_shell, NULL);
		m_shell->status = RESTORE;
		return (0);
	}
	if (scan(m_shell->lexer, "|", 2) && cmd)
	{
		exit_error("no support for `||'\n", m_shell, NULL);
		m_shell->status = RESTORE;
		return (0);
	}
	m_shell->ast = cmd;
	return (1);
}

void	reset_prompt(int sg)
{
	g_exit = 130;
	ft_putchar('\n');
	rl_on_new_line();
	rl_redisplay();
	(void)sg;
}

void	cleaning_input_and_lexer(t_shell *m_shell)
{
	if (m_shell->input)
	{
		free(m_shell->input);
		m_shell->input = NULL;
	}
	if (m_shell->lexer)
	{
		if (m_shell->lexer->str)
		{
			free(m_shell->lexer->str);
			m_shell->lexer->str = NULL;
		}
		free(m_shell->lexer);
		m_shell->lexer = NULL;
	}
}
