/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_errors_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:39:36 by pevieira          #+#    #+#             */
/*   Updated: 2024/07/17 12:14:26 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_print_serror(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
}

void	cleaning_input_and_lexer(t_shell *m_shell)
{
	if (m_shell->input)
	{
		free(m_shell->input);
		m_shell->input = NULL;
	}
	if (m_shell->lexer)
	{
		if (m_shell->lexer->str)
		{
			free(m_shell->lexer->str);
			m_shell->lexer->str = NULL;
		}
		free(m_shell->lexer);
		m_shell->lexer = NULL;
	}
}
