/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:34:01 by pevieira          #+#    #+#             */
/*   Updated: 2024/07/15 21:47:48 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*parse_id(t_lexer *lexer, int double_q, int single_q, t_shell *m_shell)
{
	char	*value;
	int		beggining;

	value = ft_calloc(1, sizeof(char));
	while (!(ft_strchr(WSPACES, lexer->c)) || ((!(double_q == 0) \
		|| !(single_q == 0)) && lexer->c))
	{
		if (lexer->c == '"' && single_q == CLOSE)
			double_q = !double_q;
		if (lexer->c == '\'' && double_q == CLOSE)
			single_q = !single_q;
		else if (lexer->c == '$' && single_q == CLOSE && !m_shell->heredoc)
		{
			beggining = lexer->i;
			value = handle_var_expand(lexer, value, m_shell);
			if (check_wspaces(value))
				value = change_lexer(lexer, value, beggining);
			continue ;
		}
		else if (ft_strchr(SYMBOLS, lexer->c) && !single_q && !double_q)
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
