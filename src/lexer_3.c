/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biltes <biltes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:04:30 by pevieira          #+#    #+#             */
/*   Updated: 2024/07/02 17:20:33 by biltes           ###   ########.fr       */
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
