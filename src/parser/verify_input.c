/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:35:53 by pevieira          #+#    #+#             */
/*   Updated: 2024/07/18 16:14:42 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	prepare_and_initial_check(t_shell *m_shell, char *ch)
{
	m_shell->input = ft_strtrim(m_shell->input, WSPACES);
	if (m_shell->input && ft_strchr("&", m_shell->input[0]))
	{
		if (ft_strchr("&", m_shell->input[1]))
			return (exit_error(\
				"syntax error near unexpected token `&&'", m_shell, NULL));
	}
	if (m_shell->input && ft_strchr("&|", m_shell->input[0]))
	{
		ch = ft_strchr("&|", m_shell->input[0]);
		return (exit_error("syntax error near unexpected token ", m_shell, ch));
	}
	else if (m_shell->input && ft_strchr(";", m_shell->input[0]))
	{
		ch = ft_strchr(";", m_shell->input[0]);
		return (exit_error("unable to start with token ", m_shell, ch));
	}
	else if (m_shell->input && ft_strchr("&|", \
		m_shell->input[ft_strlen(m_shell->input) - 1]))
	{
		ch = ft_strchr("&|", \
			m_shell->input[ft_strlen(m_shell->input) - 1]);
		return (exit_error("no support for open ", m_shell, ch));
	}
	return (0);
}

static int	check_redirection_syntax(t_shell *m_shell, int i)
{
	int	j;

	j = i + 1;
	if (m_shell->input[j] == '<' || m_shell->input[j] == '>')
		j++;
	while (ft_strchr(WSPACES, m_shell->input[j]) && m_shell->input[j])
		j++;
	if (m_shell->input[j] == '.' && (m_shell->input[j + 1] == ' ' \
		|| m_shell->input[j + 1] == '\0'))
		return (exit_error(\
		"syntax error near unexpected token `.'", m_shell, NULL));
	if (m_shell->input[j] == '>' && (m_shell->input[j + 1] == '>'))
		return (exit_error("syntax error near unexpected `>>'", m_shell, NULL));
	if (m_shell->input[j] == '>')
		return (exit_error("syntax error near unexpected `>'", m_shell, NULL));
	if (m_shell->input[j] == '<' && (m_shell->input[j + 1] == '<'))
		return (exit_error("syntax error near unexpected `<<'", m_shell, NULL));
	if (m_shell->input[j] == '<')
		return (exit_error("syntax error near unexpected `<'", m_shell, NULL));
	if (m_shell->input && ft_strchr("<>", \
		m_shell->input[ft_strlen(m_shell->input) - 1]))
		return (exit_error(\
			"syntax error near unexpected token `newline'", m_shell, NULL));
	return (0);
}

int	check_syntax(t_shell *shell, int d_q, int s_q, int i)
{
	if (prepare_and_initial_check(shell, NULL))
		return (1);
	while (shell->input && shell->input[++i])
	{
		if (shell->input[i] == '"' && s_q == CLOSE)
			d_q = !d_q;
		if (shell->input[i] == '\'' && d_q == CLOSE)
			s_q = !s_q;
		if (shell->input[i] == '&' && !s_q && !d_q)
		{
			if (shell->input[i + 1] == '&' || shell->input[i - 1] == '&')
				return (exit_error("no support for `&&'", shell, NULL));
			return (exit_error("syntax error near token ", shell, "&"));
		}
		if (shell->input[i] == ';' && !s_q && !d_q)
			return (exit_error("no support for `;'", shell, NULL));
		if (shell->input[i] == '*' && !s_q && !d_q)
			return (exit_error("no support for `*'", shell, NULL));
		if ((shell->input[i] == '<' || shell->input[i] == '>') && !s_q && !d_q)
			if (check_redirection_syntax(shell, i))
				return (1);
	}
	if (s_q == OPEN || d_q == OPEN)
		return (exit_error("no support for open quotes", shell, NULL));
	return (0);
}

static char	*prompt_generator(void)
{
	char	*prompt;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	prompt = ft_strjoin("MS ", cwd);
	free(cwd);
	cwd = ft_strjoin(prompt, ":$ ");
	free(prompt);
	return (cwd);
}

int	get_input(t_shell *m_shell)
{
	signals_set(RESTORE, m_shell);
	m_shell->prompt = prompt_generator();
	m_shell->input = readline(m_shell->prompt);
	if (m_shell->prompt)
		free(m_shell->prompt);
	if (!m_shell->input)
	{
		printf("exit\n");
		g_exit = 0;
		m_shell->status = STOP;
		return (1);
	}
	if (!m_shell->input[0])
	{
		free(m_shell->input);
		return (1);
	}
	m_shell->status = CONTINUE;
	add_history(m_shell->input);
	if (check_syntax(m_shell, CLOSE, CLOSE, -1))
		return (1);
	if (m_shell->input)
		m_shell->lexer = init_lexer(m_shell->input);
	return (0);
}
