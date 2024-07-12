/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:22:31 by pevieira          #+#    #+#             */
/*   Updated: 2024/07/12 11:35:17 by pevieira         ###   ########.fr       */
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
			printf("minishell: parsing string lexer error\n");
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

char	*insert_str(char *original, char *to_insert, int position, int jl)
{
	int		original_len;
	int		new_len;
	char	*new_str;
	int		i;
	int		j;

	original_len = ft_strlen(original);
	new_len = original_len + ft_strlen(to_insert) - (jl - position);
	i = -1;
	j = -1;
	if (position < 0 || position > original_len)
		return (NULL);
	new_str = ft_calloc((new_len + 1), sizeof(char));
	while (++i < position)
		new_str[i] = original[i];
	while (++j < (int)ft_strlen(to_insert))
		new_str[i + j] = to_insert[j];
	while (original[i + jl])
		new_str[(i++) + j] = original[jl++];
	new_str[new_len] = '\0';
	free(original);
	return (new_str);
}

int	check_wspaces(char *arg)
{
	int		squote;
	int		dquote;
	int		i;

	i = 0;
	dquote = 0;
	squote = 0;
	while (arg[i])
	{
		if (arg[i] == '"' && !squote)
			dquote = !dquote;
		if (arg[i] == '\'' && !dquote)
			squote = !squote;
		if (ft_strchr(SPACES, arg[i]) && !squote && !dquote)
			return (1);
		i++;
	}
	return (0);
}

char	*change_lexer(t_lexer *lexer, char *value, int current_i)
{
	lexer->str = insert_str(lexer->str, value, current_i, lexer->i);
	lexer->i = current_i;
	lexer->str_len = ft_strlen(lexer->str);
	lexer->c = lexer->str[lexer->i];
	skip_wspaces_lexer(lexer);
	return (reset_value(value));
}
