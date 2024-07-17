/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:41:54 by pevieira          #+#    #+#             */
/*   Updated: 2024/07/17 10:52:32 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*init_token(int type, char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(struct s_token));
	token->type = type;
	token->value = value;
	return (token);
}

