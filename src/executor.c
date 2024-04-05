/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:16:48 by pevieira          #+#    #+#             */
/*   Updated: 2024/03/28 23:48:51 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	execute_pipe(t_pipe_node *cmd)
{
    t_exec_node *leftnode= (t_exec_node *) cmd->left;
    t_exec_node *rightnode= (t_exec_node *) cmd->right;
    printf("leftnode tipo-> %d\n", leftnode->type);
    printf("right tipo-> %d\n", rightnode->type);
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
    //else if (m_shell->ast->type == EXEC)

    //else if (m_shell->ast->type == REDIR)
    
    //else if (m_shell->ast->type == HERE_DOC)
    printf("first node ast (%d)\n", m_shell->ast->type);
}