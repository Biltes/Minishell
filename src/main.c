/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:35:53 by pevieira          #+#    #+#             */
/*   Updated: 2024/03/29 11:59:57 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_exit;

int	check_syntax(t_shell *m_shell)
{
	//char *tmp;
	int i;
	int double_quotes;
	int single_quotes;
	
	i = -1;
	double_quotes = CLOSE; 
	single_quotes = CLOSE;
	//tmp = m_shell->input;
	//(void) tmp;
	m_shell->input = ft_strtrim(m_shell->input, WSPACES); //LEAK
	if (ft_strchr("&;|", m_shell->input[0]))
		return(exit_error("Can't start with that operator", m_shell));
	else if (ft_strchr("&|<>", m_shell->input[ft_strlen(m_shell->input) - 1]))
		return(exit_error("Open | or || or && not supported", m_shell));
	while (m_shell->input[++i])
	{
		if (m_shell->input[i] == '"' && single_quotes == CLOSE)
			double_quotes = !double_quotes;
		if (m_shell->input[i] == '\'' && double_quotes== CLOSE)
			single_quotes = !single_quotes;
		if (m_shell->input[i] == '&' && !single_quotes && !double_quotes)
		{
			if (m_shell->input[i + 1] != '&' && m_shell->input[i - 1]  != '&')
				return(exit_error("nao é possivel single &", m_shell));

		}
	}
	if (single_quotes == OPEN || double_quotes == OPEN)
		return (exit_error("em aberto", m_shell));
	return (1);
}

int get_input(t_shell *m_shell)
{	
	m_shell->prompt = getcwd(NULL, 0);
	m_shell->prompt = ft_strjoin(m_shell->prompt, ":$ ");
	signals_set(RESTORE, m_shell);
	m_shell->input= readline(m_shell->prompt);
	if (!m_shell->input)  // EOF ou erro
    {
        free(m_shell->prompt);  // Liberar prompt antes de sair
        return 0;  // Sair da função, indicando que não há mais entrada
    }

    if (!m_shell->input[0])  // Input vazio
    {
        free(m_shell->input);  // Liberar input antes de continuar
        free(m_shell->prompt);  // Liberar prompt também
        return 1;  // Continuar o loop, tratando como input vazio
    }
	/*if (!m_shell->input)
    	return (exit_error("definir erro1\n", m_shell));
	if(!m_shell->input[0])
		return (exit_error("definir erro1\n", m_shell));*/
	m_shell->lexer = init_lexer(m_shell->input); //LEAK!!!
	m_shell->status = CONTINUE;
	free(m_shell->prompt);
	add_history(m_shell->input);
	if (!check_syntax(m_shell)) 
		return (exit_error("definir erro2", m_shell));
	return (1);
}

int main(int ac, char **av, char **envp)
{
	t_shell m_shell;
	
	(void)ac;
	(void)av;
	(void)envp;
	g_exit = 0;
	m_shell = (t_shell){0};
	while (1)
	{
		

    	if (!get_input(&m_shell))  // Se get_input retorna 0, sair do loop LEAK!!!
        	break;

    	if (m_shell.input && parser(&m_shell))
        	executor(&m_shell);
    
    	free_cmd(m_shell.ast);  // Assegura a liberação da memória alocada

		/*
		if (get_input(&m_shell) && m_shell.input)
		{
				if (parser(&m_shell))
					executor(&m_shell);
				free_cmd(m_shell.ast);
		}
		else if (m_shell.input)
			signals_set(EXIT, &m_shell);
		else
			break;
		printf("linha-> %s\n", m_shell.input);*/
	}
	return (0);
}