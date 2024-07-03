/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:21:07 by pevieira          #+#    #+#             */
/*   Updated: 2024/07/03 11:42:31 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	scan(t_lexer *lexer, char *op, int mode)
{
	int	cur_index;
	int	end;

	cur_index = lexer->i - 1;
	end = lexer->str_len - 1;
	while (cur_index < end && ft_strchr(WSPACES, lexer->str[cur_index]))
		cur_index++;
	if (mode == 2)
		return (cur_index < end
			&& ft_strchr(op, lexer->str[cur_index])
			&& lexer->str[cur_index + 1] == lexer->str[cur_index]);
	return (cur_index < end \
		&& ft_strchr(op, lexer->str[cur_index]) \
			&& lexer->str[cur_index + 1] != lexer->str[cur_index]);
}

int	parser(t_shell *m_shell)
{
	init_ast(m_shell);
	return (1);
}
