/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:35:53 by pevieira          #+#    #+#             */
/*   Updated: 2024/07/15 17:37:10 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	prepare_and_initial_check(t_shell *m_shell, char *char_error)
{
	m_shell->input = ft_strtrim(m_shell->input, WSPACES);
	if (m_shell->input && ft_strchr("&;|", m_shell->input[0]))
	{
		char_error = ft_strchr("&;|", m_shell->input[0]);
		free(m_shell->input);
		return (exit_error("unable to start with ", m_shell, char_error));
	}
	else if (m_shell->input && ft_strchr("&|", \
		m_shell->input[ft_strlen(m_shell->input) - 1]))
	{
		char_error = ft_strchr("&|", \
			m_shell->input[ft_strlen(m_shell->input) - 1]);
		free(m_shell->input);
		return (exit_error("no support for open ", m_shell, char_error));
	}
	/*else if (!m_shell->input)
		return (1);
	(void)char_error;*/
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
		"syntax error near unexpected token `.'\n", m_shell, NULL));
	if (m_shell->input[j] == '>' && (m_shell->input[j + 1] == '>'))
		return (exit_error("syntax error near `>>'\n", m_shell, NULL));
	if (m_shell->input[j] == '>')
		return (exit_error("syntax error near `>'\n", m_shell, NULL));
	if (m_shell->input[j] == '<' && (m_shell->input[j + 1] == '<'))
		return (exit_error("syntax error near `<<'\n", m_shell, NULL));
	if (m_shell->input[j] == '<')
		return (exit_error("syntax error near `<'\n", m_shell, NULL));
	if (m_shell->input && ft_strchr("<>", \
		m_shell->input[ft_strlen(m_shell->input) - 1]))
		return (exit_error( \
			"syntax error near unexpected token `newline'\n", m_shell, NULL));
	return (0);
}


int	check_syntax(t_shell *shell, int d_q, int s_q, int i)
{
	if (prepare_and_initial_check(shell, NULL))
		return (1);
	while (shell->input[++i])
	{
		if (shell->input[i] == '"' && s_q == CLOSE)
			d_q = !d_q;
		if (shell->input[i] == '\'' && d_q == CLOSE)
			s_q = !s_q;
		if (shell->input[i] == '&' && !s_q && !d_q)
		{
			if (shell->input[i + 1] == '&' || shell->input[i - 1] == '&')
				return (exit_error("no support for `&&'\n", shell, NULL));
			return (exit_error("syntax error near token ", shell, "&"));
		}
		if (shell->input[i] == ';' && !s_q && !d_q)
			return (exit_error("no support for `;'\n", shell, NULL));
		if (shell->input[i] == '*' && !s_q && !d_q)
			return (exit_error("no support for `*'\n", shell, NULL));
		if ((shell->input[i] == '<' || shell->input[i] == '>') && !s_q && !d_q)
			if (check_redirection_syntax(shell, i))
				return (1);
	}
	if (s_q == OPEN || d_q == OPEN)
		return (exit_error("no support for open quotes\n", shell, NULL));
	return (0);
}

static char	*get_prompt(void)
{
	char	*cwd;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	prompt = ft_strjoin("🐣 ", cwd);
	free(cwd);
	cwd = ft_strjoin(prompt, ":$ ");
	free(prompt);
	return (cwd);
}

int	get_input(t_shell *m_shell)
{
	signals_set(RESTORE, m_shell);
	m_shell->prompt = get_prompt();
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
	m_shell->lexer = init_lexer(m_shell->input);
	return (0);
}
