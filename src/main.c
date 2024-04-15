/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:35:53 by pevieira          #+#    #+#             */
/*   Updated: 2024/04/15 18:13:36 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_exit;

//NAo esta a limpar bem as redire;oes. ou se calahr na oesta a criar bem

int	check_syntax(t_shell *m_shell)
{
	char *tmp;
	int i;
	int double_quotes;
	int single_quotes;
	char *trimmed_input;

	i = -1;
	double_quotes = CLOSE; 
	single_quotes = CLOSE;
	tmp = m_shell->input;
	trimmed_input = ft_strtrim(m_shell->input, WSPACES); // Aloca e trimma a entrada
	if (tmp != NULL) 
		free(tmp); 

	m_shell->input = trimmed_input; // Atribui a string trimmada de volta para m_shell->input

	if (ft_strchr("&;|", m_shell->input[0]))
		return(exit_error("Can't start with that operator\n", m_shell));
	else if (ft_strchr("&|<>", m_shell->input[ft_strlen(m_shell->input) - 1]))
		return(exit_error("Open | or || or && not supported\n", m_shell));
	while (m_shell->input[++i])
	{
		if (m_shell->input[i] == '"' && single_quotes == CLOSE)
			double_quotes = !double_quotes;
		if (m_shell->input[i] == '\'' && double_quotes== CLOSE)
			single_quotes = !single_quotes;
		if (m_shell->input[i] == '&' && !single_quotes && !double_quotes)
		{
			if (m_shell->input[i + 1] != '&' && m_shell->input[i - 1]  != '&')
				return(exit_error("minishell: no support for operator '&'\n", m_shell));

		}
		if (m_shell->input[i] == ';' && !single_quotes && !double_quotes)
			return(exit_error("minishell: no support for operator ';'\n", m_shell));
		if (m_shell->input[i] == '*' && !single_quotes && !double_quotes)
			return(exit_error("minishell: no support for operator '*'\n", m_shell));
	}
	if (single_quotes == OPEN || double_quotes == OPEN)
		return (exit_error("Open single or double quotes not supported.\n", m_shell));
	return (1);
}

static char	*get_prompt(void)
{
	char	*cwd;
	char	*prompt;
	//(NULL, 0)
	cwd = getcwd(NULL, 0);
	prompt = ft_strjoin("🐣 ", cwd);
	free(cwd);
	cwd = ft_strjoin(prompt, ":$ ");
	free(prompt);
	return (cwd);
}



int get_input(t_shell *m_shell)
{	

	m_shell->prompt = get_prompt();
	signals_set(RESTORE, m_shell);
	m_shell->input= readline(m_shell->prompt);
	free(m_shell->prompt);
	if (!m_shell->input)
    {
        free(m_shell->prompt);
        return 0;
    }

    if (!m_shell->input[0])
    {
        free(m_shell->input);
        return 1;  
    }
	m_shell->lexer = init_lexer(m_shell->input);
	m_shell->status = CONTINUE;
	add_history(m_shell->input);
	if (!check_syntax(m_shell)) 
		return (exit_error("Syntax error detected.\n", m_shell));
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
		if(m_shell.input)
		{
			free(m_shell.input);
			m_shell.input = NULL;
		}
    	if (m_shell.lexer)
		{
			if (m_shell.lexer->str)
				free(m_shell.lexer->str);
        	free(m_shell.lexer);
		}
	}
	return (0);
}