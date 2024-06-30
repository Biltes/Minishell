/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:03:14 by pevieira          #+#    #+#             */
/*   Updated: 2024/06/30 21:28:06 by pevieira         ###   ########.fr       */
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

t_token	*parsing_id_lexer(t_lexer *lexer, int double_quotes, int single_quotes, t_shell *m_shell)
{
	char	*value;

	value = calloc(1, sizeof(char));
	value[0] = '\0';
	while (!(ft_strchr(WSPACES, lexer->c)) || \
		((!(double_quotes == CLOSE) || !(single_quotes == CLOSE)) && lexer->c))
	{
		if (lexer->c == '"' && single_quotes == CLOSE)
			double_quotes = !double_quotes;
		if (lexer->c == '\'' && double_quotes == CLOSE)
			single_quotes = !single_quotes;
		else if (lexer->c == '$' && single_quotes == CLOSE)
		{
			value = handle_variable_expansion(lexer, value, m_shell);
			continue ;
		}
		else if (ft_strchr(SYMBOLS, lexer->c) \
			&& !single_quotes && !double_quotes)
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

char	*handle_variable_expansion(t_lexer *lexer, char *current_value, t_shell *m_shell)
{
	char	*var_name;
	char	*value;
	char	*new_value;

	increment_lexer(lexer);
	var_name = calloc(1, sizeof(char));
	if (lexer->c == '\0' || lexer->c == ' ')
		value = "$";
	else
	{
		while (ft_isalnum(lexer->c) || lexer->c == '_' || lexer->c == '?')
		{
			var_name = char_append(lexer, var_name);
			increment_lexer(lexer);
		}
		if (strcmp(var_name, "?") == 0)
			value = status_handler();
		else
		{
			value = env_get(var_name, m_shell);
			//value = getenv(var_name);
		}
		if (!value)
			value = "";
	}
	new_value = calloc(strlen(current_value) + strlen(value) + 1, sizeof(char));
	strcpy(new_value, current_value);
	strcat(new_value, value);
	free(var_name);
	free(current_value);
	return (new_value);
}
