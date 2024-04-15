/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:16:48 by pevieira          #+#    #+#             */
/*   Updated: 2024/04/15 16:45:30 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	execute_pipe(t_pipe_node *cmd)
{
    t_exec_node *leftnode= (t_exec_node *) cmd->left;
    t_exec_node *rightnode= (t_exec_node *) cmd->right;
    t_token *tokenzinho;
    tokenzinho = leftnode->tokens_argv[0];
    if (tokenzinho)
        printf("existe e é: %s\n", tokenzinho->value);
    tokenzinho = leftnode->tokens_argv[1];
    if (tokenzinho)
        printf("existe do primeiro 2 arg e é: %s\n", tokenzinho->value);
    
    tokenzinho = rightnode->tokens_argv[0];
    if (tokenzinho)
        printf("existe e é: %s\n", tokenzinho->value);
}
void    executor(t_shell *m_shell)
{
    if (m_shell->ast->type == PIPE)
        execute_pipe((t_pipe_node *) m_shell->ast);
    usleep(1000); // SE TIRAR ISTO DA SEG FAULT!! PQ

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