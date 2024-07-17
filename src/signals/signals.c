/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:59:45 by pevieira          #+#    #+#             */
/*   Updated: 2024/07/17 11:03:49 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	reset_prompt(int sig)
{
	(void)sig;
	g_exit = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	child_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit = 130;
		write(1, "\n", 1);
		exit(g_exit);
	}
}

void	ctrl_c_slash(int sig)
{
	g_exit = 131;
	if (sig == SIGINT)
		write(1, "\n", 1);
	if (sig == SIGQUIT)
		ft_putendl_fd("Quit (core dumped)", 1);
}


void	signals_set(int sg, t_shell *m_shell)
{
	if (sg == RESTORE)
	{
		signal(SIGINT, reset_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sg == SIGCHILD)
	{
		signal(SIGINT, ctrl_c_slash);
		signal(SIGQUIT, ctrl_c_slash);
	}
	if (sg == SIGIGNORE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sg == HEREDOC)
		signal(SIGINT, child_signal_handler);
	if (sg == EXIT)
		clean_exit(m_shell, BUILTIN_EXIT);
}
