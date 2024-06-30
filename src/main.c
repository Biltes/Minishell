/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:35:53 by pevieira          #+#    #+#             */
/*   Updated: 2024/06/30 21:09:13 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_exit;

static int	prepare_and_initial_check(t_shell *m_shell)
{
	char	*tmp;

	tmp = m_shell->input;
	m_shell->input = ft_strtrim(m_shell->input, WSPACES);
	if (tmp == NULL)
		free(tmp);
	else if (ft_strchr("&;|>", m_shell->input[0]))
	{
		free(m_shell->input);
		return (exit_error("Can't start with that operator\n", m_shell));
	}
	else if (ft_strchr("&|<>", m_shell->input[ft_strlen(m_shell->input) - 1]))
	{
		free(m_shell->input);
		return (exit_error("Open | or || or && not supported\n", m_shell));
	}
	return (0);
}

static int check_redirection_syntax(t_shell *m_shell, int i)
{
    int j;

    j = i + 1;
    while (ft_strchr(WSPACES, m_shell->input[j]))
        j++;
    if (m_shell->input[j] == '.' && (m_shell->input[j + 1] == ' ' || m_shell->input[j + 1] == '\0'))
        return (exit_error("minishell: syntax error near unexpected token `.'\n", m_shell));
    return (0);
}


int	check_syntax(t_shell *m_shell, int double_quotes, int single_quotes, int i)
{
	if (prepare_and_initial_check(m_shell))
		return (1);
	while (m_shell->input[++i])
	{
		if (m_shell->input[i] == '"' && single_quotes == CLOSE)
			double_quotes = !double_quotes;
		if (m_shell->input[i] == '\'' && double_quotes == CLOSE)
			single_quotes = !single_quotes;
		if (m_shell->input[i] == '&' && !single_quotes && !double_quotes)
		{
			if (m_shell->input[i + 1] != '&' && m_shell->input[i - 1] != '&')
				return (exit_error("minishell: no support for '&'\n", m_shell));
		}
		if (m_shell->input[i] == ';' && !single_quotes && !double_quotes)
			return (exit_error("minishell: no support for ';'\n", m_shell));
		if (m_shell->input[i] == '*' && !single_quotes && !double_quotes)
			return (exit_error("minishell: no support for '*'\n", m_shell));
		if ((m_shell->input[i] == '<' || m_shell->input[i] == '>') \
			&& !single_quotes && !double_quotes)
			if (check_redirection_syntax(m_shell, i))
				return (1);
	}
	if (single_quotes == OPEN || double_quotes == OPEN)
		return (exit_error("Open quotes not supported.\n", m_shell));
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
	m_shell->envp = NULL;
	m_shell->input = readline(m_shell->prompt);
	if (m_shell->prompt)
		free(m_shell->prompt);
	if (!m_shell->input) // Detecta CTRL-D
	{
		printf("quit minishell\n");
		g_exit = 0; // Define o código de saída para 0
		m_shell->status = STOP; // Define o status para STOP para encerrar o loop
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
		return (1); //exit_error("Syntax error detected.\n", m_shell)
	m_shell->lexer = init_lexer(m_shell->input);
	return (0);
}
void init_env(t_shell *shell, char **envp)
{
    shell->env = NULL;
    shell->envp = NULL;
    shell->envp_size = 0;
    envp_to_list(envp, shell);
    envp_update(shell);
    //printf("Initial environment:\n");
    //envp_print(shell);
}

int main(int ac, char **av, char **envp)
{
    t_shell m_shell;

    (void)ac;
    (void)av;
    g_exit = 0;
    m_shell = (t_shell){0};
    init_env(&m_shell, envp);
    m_shell.status = CONTINUE; // Initialize the status to CONTINUE

	while (m_shell.status == CONTINUE) // Continue as long as the status is CONTINUE
	{
		if (get_input(&m_shell))
			continue;
		if(m_shell.input[0])
		{
			if (parser(&m_shell))
				executor(&m_shell);
		}
		free_cmd(m_shell.ast);
        cleaning_input_and_lexer(&m_shell);
        // If the exit command was entered, break the loop
        if (m_shell.status == STOP)
            break;
    }

    // Clean up
	if (m_shell.ast)
		free_cmd(m_shell.ast);
	cleaning_input_and_lexer(&m_shell);
    // Return the exit status
    return (g_exit);
}
