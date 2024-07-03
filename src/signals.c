/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:25:23 by pevieira          #+#    #+#             */
/*   Updated: 2024/07/03 14:52:38 by pevieira         ###   ########.fr       */
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
