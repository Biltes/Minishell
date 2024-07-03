/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:59:45 by pevieira          #+#    #+#             */
/*   Updated: 2024/07/03 11:00:55 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	reset_prompt(int sig)
{
	(void)sig;
	g_exit = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	signals_set(int sg, t_shell *m_shell)
{
	if (sg == RESTORE)
	{
		signal(SIGINT, reset_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sg == QUIT)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
	if (sg == EXIT)
	{
		clean_exit(m_shell, BUILTIN_EXIT);
	}
	if (sg == HEREDOC)
		signal(SIGINT, child_signal_handler);
	if (sg == HEREDOC_PAUSE)
		signal(SIGINT, child_signal_handler2);
	if (sg == SIGCHILD)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
