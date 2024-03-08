/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:38:21 by pevieira          #+#    #+#             */
/*   Updated: 2024/03/08 10:19:25 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>


# define WSPACES " \t\n\v\f\r"
# define OPERATORS "|><&()"
/*

Estrutura da Shell 
    lexer
    parser
    ast
    executor
    envp
    status

Estrutura Lexer
	char c;
	unsigned int index;
	char *string completa;

Estrutura de tokens:
	enum type
		token id
		token =
		token string
		token ;
		token r (
		token l )
	
	char *value

Estrutura AST:
	enum type
		 função
		variável definição
		ast variabel
		ast string
		ast bloco
	
	struct ast * variabel definição value

	char *variavel nome

	char *funlçao nome
	struct asa ** argumentos da funçao
	size_t tamanho dos argumentos

	char *sttringvalue

	ast ** bloco valor
	size_t command size

Estrutura parser
	lexer 
	current token
*/
#endif