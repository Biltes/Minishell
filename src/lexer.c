/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:17:32 by pevieira          #+#    #+#             */
/*   Updated: 2024/04/20 22:40:49 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_lexer	*init_lexer(char *str)
{
	t_lexer	*lexer;

	lexer = ft_calloc(1, sizeof(struct s_lexer));
	lexer->str = ft_strdup(str);
	lexer->i = 0;
	lexer->c = str[lexer->i];
	lexer->str_len = ft_strlen(str);
	return (lexer);
}

//FICA ENTRE AS PROXIMAS DUAS FUN;OES QUANDO TERMINA COM MAIS DE 1 ESPACO
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
	while (ft_strchr(WSPACES, lexer->c))
	{
		increment_lexer(lexer);
		printf("oi?\n");
	}
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c && lexer->i < ft_strlen(lexer->str))
	{
		if ((ft_strchr(WSPACES, lexer->c)))
		{
			printf("entrou aqui4\n\n");
			skip_wspaces_lexer(lexer);
		}
		else if (lexer->c == '|')
		{
			printf("entrou aqui3\n\n");
			return (increment_lexer_and_token(lexer, \
				init_token(TOKEN_PIPE, char_to_str(lexer))));
		}
		else if (lexer->c == '<' || lexer->c == '>')
			return (parsing_redirections_lexer1(lexer));
		else if (lexer->c)
			return (parsing_id_lexer(lexer, CLOSE, CLOSE));
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
				init_token(TOKEN_REDIR3, ft_strdup("<<"))));
		value = ft_strdup("<");
	}
	else if (lexer->c == '>' )
	{
		type = TOKEN_REDIR2;
		increment_lexer(lexer);
		if (lexer->c == '>')
			return (increment_lexer_and_token(lexer, \
				init_token(TOKEN_REDIR4, ft_strdup(">>"))));
		value = ft_strdup("<");
	}
	return (init_token(type, value));
}
