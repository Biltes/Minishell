/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:04:30 by pevieira          #+#    #+#             */
/*   Updated: 2024/07/15 11:39:33 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*char_append(t_lexer *lexer, char *value)
{
	char	*cs;
	char	*tmp;

	cs = char_to_str(lexer);
	tmp = ft_strjoin(value, cs);
	free(value);
	free(cs);
	return (tmp);
}

char	*status_handler(void)
{
	char	*status_str;

	status_str = ft_itoa(g_exit);
	if (status_str == NULL)
	{
		printf("minishell: failed to allocate memory for status string\n");
		return (NULL);
	}
	return (status_str);
}

char	*expand_v(t_lexer *lexer, t_shell *shell, char *var_name, char *value)
{
	increment_lexer(lexer);
	var_name = calloc(1, sizeof(char));
	if (lexer->c == '\0' || lexer->c == ' ' || lexer->c == '"')
		value = "$";
	else
	{
		while (ft_isalnum(lexer->c) || lexer->c == '_')
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
			value = env_get(var_name, shell);
		if (!value)
			value = "";
	}
	free(var_name);
	return (value);
}

char	*handle_var_expand(t_lexer *lexer, char *cur_value, t_shell *m_shell)
{
	char	*value;
	char	*new_value;
	char	*var_name;

	var_name = NULL;
	value = NULL;
	value = expand_v(lexer, m_shell, var_name, value);
	free(var_name);
	new_value = calloc(strlen(cur_value) + strlen(value) + 1, sizeof(char));
	strcpy(new_value, cur_value);
	strcat(new_value, value);
	free(cur_value);
	return (new_value);
}

char	*reset_value(char *value)
{
	char	*new_value;

	new_value = calloc(1, sizeof(char));
	new_value[0] = '\0';
	free(value);
	return (new_value);
}
