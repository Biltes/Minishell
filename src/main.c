/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:35:53 by pevieira          #+#    #+#             */
/*   Updated: 2024/03/08 10:22:07 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int ac, char **av, char **envp)
	criação da estrutura shell
	nulo av e ac
	iniciação a estrutura da shell
		Igualar a NULOS   cmd, linha, varivavel  ambiente, e o seu tamanho
		tratar variável ambiente (ns)

	
	loop durante a shell
		sinal para encerrar caso receba ctrl d
		atualizar estrutura shell
		get_prompt (obtençao do caminho) / readline 
		verificação se algo foi submetido
		lexer     https://www.youtube.com/watch?v=Tfhm0yQ9P8Q
			PREPARA  a linha digitada pelo usuario para processar e faz verificação
			adiciona ao histórico de comandos
			verifica se esta vazia
			remove espaços extra do inicio e fim da linha
			verifica se tem erros de syntax
			Adiciona espaços se necessarios para efetuar um trim correto
			TROCA OS ESPAÇOS DA LINHA DE COMANDO por caracteres nULOS
			get token
		
		parser  Criação da AST  https://www.youtube.com/watch?v=4HW3RAoWMpg
			Verificação do tipo e criação da ast
			criacao de node de redirecionamento
			 função que cria um node de pipe
			cria um node de execução 
			cria um node de operação lógica OR ||
			cria um node de bloco de comandos na AST.

		executor



	limpar historia
	destruir variável de ambiente
	Free arrays
	verifica se estamos conectados a um outro terminal e printa exit nesse terminal

/*

xer  is the process of converting a sequence of characters into a sequence of tokens.
int	main(int argc, char **argv, char **envp)
{
	signal_handler();
	while (!SIGQUIT && cmd != NULL)
	{
		char	*line = readline();

		if (line == NULL || !strcmp(line, "exit"))
			exit;
		if (lexer(line))
		{
			t_data *data = parser(line, envp);
			execution(data, envp);
		}
	}
	return (0);
}

*/