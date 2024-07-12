/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:24:40 by pevieira          #+#    #+#             */
/*   Updated: 2024/07/12 11:35:54 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define WSPACES " \t\f\n\v\r"
# define SYMBOLS "<>|"
# define MAXARG 50

# define OPEN 1
# define CLOSE 0

# define EXEC 1
# define REDIR 2
# define PIPE 3
# define LIST 4
# define BACK 5
# define BLOCK 6
# define AND 303
# define OR_OP 305
# define APPEND 306

# define TOKEN_STRING 7
# define TOKEN_SEMICOLON 8
# define TOKEN_LPARENT 9
# define TOKEN_RPARENT 10
# define TOKEN_EQUALSIGN 11
# define TOKEN_PIPE 12
# define TOKEN_AND 13
# define TOKEN_ID 14
# define TOKEN_REDIR1 15
# define TOKEN_REDIR2 16
# define TOKEN_REDIR3 17
# define TOKEN_REDIR4 18
# define HERE_DOC 19

typedef struct s_lexer
{
	char			c;
	char			*str;
	unsigned int	str_len;
	unsigned int	i;
}					t_lexer;

typedef struct s_token
{
	int		type;
	char	*value;
}			t_token;

typedef struct s_cmd
{
	int		type;
}			t_cmd;

typedef struct s_ast_pipe
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}			t_pipe_node;

typedef struct s_exec_node
{
	int		type;
	t_token	*tokens_argv[MAXARG];
}			t_exec_node;

typedef struct s_redir_node
{
	int		type;
	char	*file;
	int		mode;
	int		fd;
	t_cmd	*cmd;
}			t_redir_node;

typedef struct s_ast_list
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}			t_ast_list;

typedef struct s_parser
{
	t_lexer	*lexer;
	t_token	*current_token;
}			t_parser;

typedef struct s_here
{
	int		type;
	t_cmd	*cmd;
	char	*eof;
	int		mode;
	int		fdin;
	int		fdout;
}			t_here;

typedef struct s_shell	t_shell;

t_cmd	*init_redir_cmd(t_cmd *cmd, t_token *token, int mode, int fd);
t_cmd	*init_pipe_node(t_cmd *left, t_cmd *right);
t_cmd	*init_exec_node(void);
t_cmd	*init_block_node(t_cmd *cmd);

int		scan(t_lexer *lexer, char *op, int mode);
void	ft_add_token_to_exec(t_exec_node *exec, t_token *token);
int		init_ast(t_shell *m_shell);
char	*change_lexer(t_lexer *lexer, char *value, int current_i);
int		check_wspaces(char *arg);
#endif
