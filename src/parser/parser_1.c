/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:21:07 by pevieira          #+#    #+#             */
/*   Updated: 2024/07/18 13:14:40 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

t_token	*parse_id(t_lexer *lexer, int d_q, int s_q, t_shell *sh)
{
	char	*value;
	int		beggining;

	value = ft_calloc(1, sizeof(char));
	while (!(ft_strchr(WSPACES, lexer->c)) || ((!(d_q == 0) \
		|| !(s_q == 0)) && lexer->c))
	{
		if (lexer->c == '"' && s_q == CLOSE)
			d_q = !d_q;
		if (lexer->c == '\'' && d_q == CLOSE)
			s_q = !s_q;
		if ((lexer->c == '$' || lexer->c == '~') && s_q == 0 && !sh->heredoc)
		{
			beggining = lexer->i;
			value = handle_var_expand(lexer, value, sh, 0);
			if (check_wspaces(value))
				value = change_lexer(lexer, value, beggining);
			continue ;
		}
		else if (ft_strchr(SYMBOLS, lexer->c) && !s_q && !d_q)
			break ;
		value = char_append(lexer, value);
		increment_lexer(lexer);
	}
	return (init_token(TOKEN_ID, value));
}

char	*char_to_str(t_lexer *lexer)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

int	parser(t_shell *m_shell)
{
	return (init_ast(m_shell));
}
