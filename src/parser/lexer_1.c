/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:17:32 by pevieira          #+#    #+#             */
/*   Updated: 2024/07/17 10:52:16 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_lexer	*init_lexer(char *str)
{
	t_lexer	*lexer;

	lexer = ft_calloc(1, sizeof(struct s_lexer));
	lexer->str = ft_strdup(str);
	lexer->i = 0;
	lexer->c = lexer->str[lexer->i];
	lexer->str_len = ft_strlen(str);
	return (lexer);
}

void	increment_lexer(t_lexer *lexer)
{
	if (lexer->c && lexer->i < ft_strlen(lexer->str))
	{
		lexer->i += 1;
		lexer->c = lexer->str[lexer->i];
	}
}

void	skip_wspaces_lexer(t_lexer *lexer)
{
	while (ft_strchr(WSPACES, lexer->c) && lexer->i < ft_strlen(lexer->str))
		increment_lexer(lexer);
}

t_token	*lexer_get_next_token(t_lexer *lexer, t_shell *m_shell)
{
	while (lexer->c && lexer->i < ft_strlen(lexer->str))
	{
		if ((ft_strchr(WSPACES, lexer->c)))
			skip_wspaces_lexer(lexer);
		else if (lexer->c == '|')
		{
			return (increment_lexer_and_token(lexer, \
				init_token(TOKEN_PIPE, NULL)));
		}
		else if (lexer->c == '<' || lexer->c == '>')
			return (parsing_redirections_lexer1(lexer));
		else if (lexer->c)
			return (parse_id(lexer, CLOSE, CLOSE, m_shell));
		else
			return (NULL);
	}
	return (NULL);
}

t_token	*parsing_redirections_lexer1(t_lexer *lexer)
{
	int		type;
	char	*value;

	type = TOKEN_REDIR1;
	value = NULL;
	if (lexer->c == '<')
	{
		type = TOKEN_REDIR1;
		increment_lexer(lexer);
		if (lexer->c == '<')
			return (increment_lexer_and_token(lexer, \
				init_token(TOKEN_REDIR4, NULL)));
	}
	else if (lexer->c == '>' )
	{
		type = TOKEN_REDIR2;
		increment_lexer(lexer);
		if (lexer->c == '>')
			return (increment_lexer_and_token(lexer, \
				init_token(TOKEN_REDIR3, NULL)));
	}
	return (init_token(type, value));
}
