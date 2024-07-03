/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:03:14 by pevieira          #+#    #+#             */
/*   Updated: 2024/07/03 12:05:28 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*increment_lexer_and_token(t_lexer *lexer, t_token *token)
{
	increment_lexer(lexer);
	return (token);
}

t_token	*parsing_string_lexer(t_lexer *lexer)
{
	char	*value;
	char	*cs;
	char	*tmp;

	value = calloc(1, sizeof(char));
	value[0] = '\0';
	increment_lexer(lexer);
	while (lexer->c != '"')
	{
		if (lexer->c == '\0')
		{
			printf("\nerro3 no parsing string lexer!\n");
			return (NULL);
		}
		cs = char_to_str(lexer);
		tmp = ft_strjoin(value, cs);
		free(value);
		free(cs);
		value = tmp;
		increment_lexer(lexer);
	}
	increment_lexer(lexer);
	return (init_token(TOKEN_STRING, value));
}

t_token	*parse_id(t_lexer *lexer, int double_q, int single_q, t_shell *m_shell)
{
	char	*value;

	value = calloc(1, sizeof(char));
	value[0] = '\0';
	while (!(ft_strchr(WSPACES, lexer->c)) || \
		((!(double_q == CLOSE) || !(single_q == CLOSE)) && lexer->c))
	{
		if (lexer->c == '"' && single_q == CLOSE)
			double_q = !double_q;
		if (lexer->c == '\'' && double_q == CLOSE)
			single_q = !single_q;
		else if (lexer->c == '$' && single_q == CLOSE)
		{
			value = handle_var_expand(lexer, value, m_shell);
			continue ;
		}
		else if (ft_strchr(SYMBOLS, lexer->c) \
			&& !single_q && !double_q)
			break ;
		value = char_append(lexer, value);
		increment_lexer(lexer);
	}
	return (init_token(TOKEN_ID, value));
}

char	*char_to_str(t_lexer *lexer)
{
	char	*str;

	str = calloc (2, sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

char	*handle_var_expand(t_lexer *lexer, char *cur_value, t_shell *m_shell)
{
	char	*var_name;
	char	*value;
	char	*new_value;

	increment_lexer(lexer);
	var_name = calloc(1, sizeof(char));
	if (lexer->c == '\0' || lexer->c == ' ' || lexer->c == '"')
		value = "$";
	else
	{
		while (ft_isalnum(lexer->c) || lexer->c == '_' )
		{
			var_name = char_append(lexer, var_name);
			increment_lexer(lexer);
		}
		if (lexer->c == '?')
		{
			value = status_handler();
			increment_lexer(lexer);
		}
		else
			value = env_get(var_name, m_shell);
		if (!value)
			value = "";
	}
	new_value = calloc(strlen(cur_value) + strlen(value) + 1, sizeof(char));
	strcpy(new_value, cur_value);
	strcat(new_value, value);
	free(var_name);
	free(cur_value);
	return (new_value);
}
