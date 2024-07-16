/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:25:23 by pevieira          #+#    #+#             */
/*   Updated: 2024/07/16 14:20:46 by pevieira         ###   ########.fr       */
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
