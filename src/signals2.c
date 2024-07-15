/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:59:45 by pevieira          #+#    #+#             */
/*   Updated: 2024/07/15 17:56:04 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	reset_prompt(int sig)
{
	(void)sig;
	g_exit = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	sigint_ignore(int sig)
{
	if (sig == SIGINT)
	{
		g_exit = 130;
		ft_putstr_fd("\n", 2);
		signal(SIGINT, SIG_IGN);
	}
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
	if (sg == EXIT)
		clean_exit(m_shell, BUILTIN_EXIT);
	if (sg == HEREDOC)
		signal(SIGINT, child_signal_handler);
	if (sg == HEREDOC_PAUSE) //NAO ESTa a ser usado em nada...
		signal(SIGINT, child_signal_handler2);
	if (sg == SIGIGNORE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sg == SIGPIPE)
	{
		signal(SIGINT, sigint_ignore);
		signal(SIGQUIT, SIG_IGN);
	}
}
