/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:11:24 by pevieira          #+#    #+#             */
/*   Updated: 2024/07/16 09:41:51 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_exit;

int	main(int ac, char **av, char **envp)
{
	t_shell	m_shell;

	(void)ac;
	(void)av;
	g_exit = 0;
	m_shell = (t_shell){0};
	init_env(&m_shell, envp);
	m_shell.status = CONTINUE;
	while (m_shell.status != STOP)
	{
		if (get_input(&m_shell))
			continue ;
		signals_set(SIGIGNORE, &m_shell);
		if (m_shell.input[0])
			if (parser(&m_shell) && m_shell.status == CONTINUE)
				executor(&m_shell);
		free_cmd(m_shell.ast);
		cleaning_input_and_lexer(&m_shell);
	}
	free_array(m_shell.envp);
	envp_destroy(m_shell.env);
	return (g_exit);
}
