/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:25:23 by pevieira          #+#    #+#             */
/*   Updated: 2024/06/03 15:11:23 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	child_signal_handler2(int sig)
{
	if (sig == SIGINT)
	{
		g_exit = 130;
		signal(SIGINT, SIG_IGN);
	}
}

void	child_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit = 130;
		printf("\n");
		exit(g_exit);
	}
}

void	ctrl_c(int sig)
{
	printf("ctrl_c (SIGINT) recebido\n");
	g_exit = 130;
	ft_putchar('\n');
	(void)sig;
}

void	back_slash(int sig)
{
	g_exit = 131;
	printf("back_slash (SIGQUIT) recebido\n");
	printf("Quit (core dumped)\n");
	(void)sig;
}

static void	reset_prompt(int sig)
{
	(void)sig;
	g_exit = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signals_set(int sg, t_shell *m_shell)
{
	printf("Setting signal state: %d\n", sg);
	if (sg == RESTORE)
	{
		signal(SIGINT, reset_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sg == QUIT)
	{
		printf("entrando aqui\n");
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
	if (sg == EXIT)
	{
		printf("exit\n");
		clean_exit(m_shell, BUILTIN_EXIT);
	}
	if (sg == HEREDOC)
		signal(SIGINT, child_signal_handler);
	if (sg == HEREDOC_PAUSE)
		signal(SIGINT, child_signal_handler2);
	if (sg == SIGCHILD)
	{
		signal(SIGINT, back_slash);
		signal(SIGQUIT, back_slash);
	}
}
