/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:17:32 by pevieira          #+#    #+#             */
/*   Updated: 2024/03/29 12:04:44 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_lexer*    init_lexer(char *str)
{
    t_lexer* lexer;

    lexer = ft_calloc(1,sizeof(struct s_lexer));
    lexer->str = str;
    lexer->i = 0;
    lexer->c = str[lexer->i];
    lexer->str_len = ft_strlen(str);
    return lexer;
}

void    increment_lexer(t_lexer* lexer)
{
    if (lexer->c && lexer->i < ft_strlen(lexer->str))
    {
        lexer->i += 1;
        lexer->c = lexer->str[lexer->i];
    }
}

void    skip_wspaces_lexer(t_lexer* lexer)
{
    while (ft_strchr(WSPACES, lexer->c))
        increment_lexer(lexer);
}

t_token* lexer_get_next_token(t_lexer* lexer)
{
    while (lexer->c && lexer->i < ft_strlen(lexer->str))
    {
        if ((ft_strchr(WSPACES, lexer->c)))
            skip_wspaces_lexer(lexer);

        if (lexer->c == '"')
            return (parsing_string_lexer(lexer));
        else if (ft_isalnum(lexer->c))
            return parsing_id_lexer(lexer);
        else if (lexer->c == '=')
            return (increment_lexer_and_token(lexer, init_token(TOKEN_EQUALSIGN, char_to_str(lexer))));
        else if (lexer->c == '(')
            return (increment_lexer_and_token(lexer, init_token(TOKEN_LPARENT, char_to_str(lexer))));
        else if (lexer->c == ')')
            return (increment_lexer_and_token(lexer, init_token(TOKEN_RPARENT, char_to_str(lexer))));
        else if (lexer->c == ';')
            return (increment_lexer_and_token(lexer, init_token(TOKEN_SEMICOLON, char_to_str(lexer))));
        else if (lexer->c == '|')
            return (increment_lexer_and_token(lexer, init_token(TOKEN_PIPE, char_to_str(lexer))));
        else if(lexer->c == '<' || lexer->c == '>')
            return (parsing_redirections_lexer1(lexer));
        else
            return (NULL);
    }
    return NULL;
}
t_token *parsing_redirections_lexer1(t_lexer *lexer)
{
    int  type;
    char *value;

    type = TOKEN_REDIR1;
    value = NULL;
    if (lexer->c == '<') //Redirecionamento de Entrada, faz com que comando leia a entrada do arquivo, e não do teclado.
    {
        type = TOKEN_REDIR1;
        increment_lexer(lexer);
        if (lexer->c == '<') //heredoc
            return (increment_lexer_and_token(lexer, init_token(TOKEN_REDIR3, ft_strdup("<<"))));
        value = ft_strdup("<");
    }
    else if (lexer->c == '>' ) // redirencionamento de saida. faz com que a saída de comando seja escrita em arquivo, não exibida na tela.
    {
        type = TOKEN_REDIR2;
        increment_lexer(lexer);
        if (lexer->c =='>') // redirecionamento de saida anexado. anexa a saída do comando ao final do arquivo. Se o arquivo não existir, ele é criado.
            return (increment_lexer_and_token(lexer, init_token(TOKEN_REDIR4, ft_strdup(">>"))));
        value = ft_strdup("<");
    }
    return (init_token(type, value));

}

t_token*    increment_lexer_and_token(t_lexer* lexer, t_token* token)
{
    increment_lexer(lexer);
    return token;
}
t_token*    parsing_string_lexer(t_lexer* lexer)  //(algo muito estranho)
{
    char* value;
    char* cs;
    char* tmp;

    value= calloc(1, sizeof(char));
    value[0] = '\0';
    increment_lexer(lexer);
    while(lexer->c != '"')
    {
        if (lexer->c == '\0')
        {
            printf("\nerro3 no parsing string lexer!\n"); //COLOCAR FUNÇAO DE ERRO!
            return(NULL);
        }
        cs = char_to_str(lexer);
        tmp = ft_strjoin(value, cs);
        free(value);
        free(cs); //adiçao leaks
        value = tmp;
        increment_lexer(lexer);
    }
    increment_lexer(lexer);
    return (init_token(TOKEN_STRING, value));
}


t_token*  parsing_id_lexer(t_lexer* lexer)  //(repete caracteres)
{
    char* value;
    char* cs;
    char* tmp;

    value= calloc(1, sizeof(char));
    value[0] = '\0';
    //increment_lexer(lexer);
    while(ft_isalnum(lexer->c))
    {
        cs = char_to_str(lexer); //LEAK!!!
        tmp = ft_strjoin(value, cs);
        free(value);
        free(cs); //coloquei isto agora 
        value = tmp;
        increment_lexer(lexer);
    }
    //increment_lexer(lexer);
    return (init_token(TOKEN_ID, value));
}

char *    char_to_str(t_lexer* lexer)
{
    char* str;
    str = calloc (2, sizeof(char));  //leak???
    str[0] = lexer->c;
    str[1] = '\0';
    return (str);
}