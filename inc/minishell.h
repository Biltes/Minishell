/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:38:21 by pevieira          #+#    #+#             */
/*   Updated: 2024/03/28 20:39:21 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parser.h"
# include <readline/readline.h>
# include "../libft/libft.h"
# include <signal.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>

# define RESTORE 1
# define QUIT 2
# define EXIT 3
# define HEREDOC 4
# define HEREDOC_PAUSE 5
# define BUILTIN_EXIT 1

# define CONTINUE 1
# define STOP 0

extern int	g_exit;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				visible;
	int				index;
	struct s_env	*next;
}					t_env;

typedef struct s_shell
{
	char	*input;
	char	*prompt;
	int		line_len;
	int 	status;
	char	**envp;
	t_lexer *lexer;
	t_token	*next_token;
	t_cmd	*ast;
	t_env	**env;
} t_shell;



int parser(t_shell *m_shell);

t_token* init_token(int type, char* value);
t_lexer*    init_lexer(char *str);
void    increment_lexer(t_lexer* lexer);
void    skip_wspaces_lexer(t_lexer* lexer);
t_token* lexer_get_next_token(t_lexer* lexer);
t_token*    increment_lexer_and_token(t_lexer* lexer, t_token* token);
t_token*    parsing_string_lexer(t_lexer* lexer);
t_token*  parsing_id_lexer(t_lexer* lexer);
char *    char_to_str(t_lexer* lexer);
t_token *parsing_redirections_lexer1(t_lexer *lexer);

int exit_error(char *str, t_shell *m_shell);
void	set_signal(int sg, t_shell *msh);
void    executor(t_shell *m_shell);

void	reset_prompt(int sg);
void	child_signal_handler2(int sig);
void	child_signal_handler(int sig);
void	ctrl_c(int sig);
void	back_slash(int sig);
void	signals_set(int sg, t_shell *m_shell);

void	free_exec_node(t_exec_node *exec);

void	free_cmd(t_cmd *cmd);
void	free_array(char **array);
void	clean_exit(t_shell *m_shell, int mode);
void	envp_destroy(t_env *env);

#endif