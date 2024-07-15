/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:38:21 by pevieira          #+#    #+#             */
/*   Updated: 2024/07/15 21:49:42 by pevieira         ###   ########.fr       */
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

# define SIGRESTORE 11
# define SIGHEREDOC 21
# define SIGCHILD 31
# define SIGIGNORE 41

# define CONTINUE 101
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
	char	*pwd;
	int		line_len;
	int		status;
	int		envp_size;
	int		exec_cmd;
	int		heredoc;
	int		pid;
	char	**envp;
	t_lexer	*lexer;
	t_token	*next_token;
	t_cmd	*ast;
	t_env	*env;
}			t_shell;

int		parser(t_shell *m_shell);
int		get_input(t_shell *m_shell);
void	init_env(t_shell *shell, char **envp);
t_token	*init_token(int type, char *value);
t_lexer	*init_lexer(char *str);
void	increment_lexer(t_lexer *lexer);
void	skip_wspaces_lexer(t_lexer *lexer);
t_token	*lexer_get_next_token(t_lexer *lexer, t_shell *m_shell);
t_token	*increment_lexer_and_token(t_lexer *lexer, t_token *token);
t_token	*parsing_string_lexer(t_lexer *lexer);
t_token	*parse_id(t_lexer *lexer, int double_q, int single_q, t_shell *m_shell);
char	*char_to_str(t_lexer *lexer);
t_token	*parsing_redirections_lexer1(t_lexer *lexer);

int		exit_error(char *str, t_shell *m_shell, char *char_error);
void	set_signal(int sg, t_shell *msh);
void	executor(t_shell *m_shell);

void	child_signal_handler2(int sig);
void	child_signal_handler(int sig);
void	ctrl_c(int sig);
void	ctrl_c_slash(int sig);
void	signals_set(int sg, t_shell *m_shell);

void	free_exec_node(t_exec_node *exec);

void	free_cmd(t_cmd *cmd);
void	free_array(char **array);
void	clean_exit(t_shell *m_shell, int mode);
void	envp_destroy(t_env *env);

t_cmd	*parsing_exec_and_pipe(t_shell *m_shell);
void	cleaning_input_and_lexer(t_shell *m_shell);
char	*handle_var_expand(t_lexer *lexer, char *cur_value, t_shell *m_shell);
char	*char_append(t_lexer *lexer, char *value);
char	*status_handler(void);

t_env	*manage_env_node(char *key, char *value, int visible, int action);
t_env	*env_add_or_mod(t_shell *shell, char *key, char *value, int visible);

char	*expand_v(t_lexer *lexer, t_shell *shell, char *var_name, char *value);
void	env_add(t_shell *shell, char *key, char *value, int visible);
void	process_and_trim_arg(t_shell *shell, t_token *token, int len);
bool	env_rm(char *key, t_shell *shell);
char	*get_tilde_env_var(t_shell *sh, char *tmp);
void	env_expand(t_shell *shell, char *tmp, char **line);
int		expand_tilde(t_shell *shell, char **line);
char	*reset_value(char *value);

#endif
