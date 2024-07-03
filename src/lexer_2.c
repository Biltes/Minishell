/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   lexer_2.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: pevieira <pevieira@student.42.com>		 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/20 21:03:14 by pevieira		  #+#	#+#			 */
/*   Updated: 2024/07/03 15:28:36 by pevieira		 ###   ########.fr	   */
/*																			*/
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
