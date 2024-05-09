/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migupere <migupere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:38:21 by pevieira          #+#    #+#             */
/*   Updated: 2024/05/09 12:58:00 by migupere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>

# include "parser.h"
# include "../libft/libft.h"
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "builtins.h"
# include <errno.h>

# define RESTORE 1
# define QUIT 2
# define EXIT 3
# define HEREDOC 4
# define HEREDOC_PAUSE 5
# define BUILTIN_EXIT 1
# define ERROR_TITLE "minishell: "
# define ERROR_HERE_DOC "unexpected EOF while looking for matching `"
# define ERROR_SYNTAX "syntax error"

# define SIGRESTORE 1
# define SIGHEREDOC 2
# define SIGCHILD 3
# define SIGIGNORE 4

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
	char 	*pwd;
	int		line_len;
	int		status;
	int		envp_size;
	int		exec_cmd;
	int 	pid;
	char	**envp;
	t_lexer	*lexer;
	t_token	*next_token;
	t_cmd	*ast;
	t_env	*env;
}			t_shell;

int		parser(t_shell *m_shell);

t_token	*init_token(int type, char *value);
t_lexer	*init_lexer(char *str);
void	increment_lexer(t_lexer *lexer);
void	skip_wspaces_lexer(t_lexer *lexer);
t_token	*lexer_get_next_token(t_lexer *lexer);
t_token	*increment_lexer_and_token(t_lexer *lexer, t_token *token);
t_token	*parsing_string_lexer(t_lexer *lexer);
t_token	*parsing_id_lexer(t_lexer *lexer, int double_quotes, int single_quotes);
char	*char_to_str(t_lexer *lexer);
t_token	*parsing_redirections_lexer1(t_lexer *lexer);

int		exit_error(char *str, t_shell *m_shell);
void	set_signal(int sg, t_shell *msh);
void	executor(t_shell *m_shell);

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

t_cmd	*parsing_exec_and_pipe(t_shell *m_shell);
void	cleaning_input_and_lexer(t_shell *m_shell);
char	*handle_variable_expansion(t_lexer *lexer, char *current_value);
char	*char_append(t_lexer *lexer, char *value);
char	*status_handler(void);

t_env	*env_add(t_shell *shell, char *key, char *value, int visible);
t_env	*manage_env_node(char *key, char *value, int visible, int action);
t_env	*env_add_or_mod(t_shell *shell, char *key, char *value, int visible);

#endif
