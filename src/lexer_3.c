/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:04:30 by pevieira          #+#    #+#             */
/*   Updated: 2024/04/22 11:04:57 by pevieira         ###   ########.fr       */
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
		printf("Failed to allocate memory for status string\n");
		return (NULL);
	}
	return (status_str);
}
