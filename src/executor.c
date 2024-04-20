/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:16:48 by pevieira          #+#    #+#             */
/*   Updated: 2024/04/19 15:03:41 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	executor(t_shell *m_shell)
{
	if (m_shell->ast->type == PIPE)
		printf("hello");
	usleep(1000);
}
//Esta funcao verifica a existenicia de uma variavel de ambiente dentro do id
//Nao verifica QUANTAS SÁO, NEM O SEU VALOR.
/*
void    variable_exitence(t_token *id_node)
{
    int i;
    int single_quotes;
    int single_quotes = 0;
    i = 0;
    if (id_node->type == TOKEN_ID)
	{
        while(id_value->value[i])
        {
            if (id_value->value[i] == "'")
                single_quotes = !single_quotes;
            if(id_value->value[i] == "$")
            {
                if (single_quotes == OPEN)
                    return(0);
                i++;
                if (ft_isalnum(id_value->value[i]))
                    return (1);
            }
            i++;
        }
    }
    return(0);
}
*/
