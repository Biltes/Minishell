/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:26:55 by migupere          #+#    #+#             */
/*   Updated: 2024/07/03 15:01:01 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# define FORK_FAILURE_EXIT_CODE 127
# define FILE_PERMISSIONS 0644
# define SEGFAULT 11
# define SEGFAULT_COREDUMPED 139
# define FLOAT_EXCEPTION 8
# define FLOAT_EXCEPTION_COREDUMPED 136
# define NOT_EXP "|><&();/ \t\n\v\f\r"
# define SPACES " \t\n\v\f\r"
# include <dirent.h>
# define EXIT_SIG_OFFSET 128
# define SIGINT_EXIT_STATUS 130

void	echo_command(t_exec_node *cmd);
int		run_builtin(t_shell *shell, t_exec_node *cmd);
void	cd_command(t_shell *shell, t_exec_node *cmd);
bool	chdir_command(t_shell *shell, char *path);
int		print_error(t_shell *shell, char *msg, char *msg2, int exit);
void	env_command(t_shell *shell, t_exec_node *cmd);
void	envp_print(t_shell *shell);
void	env_export(t_shell *shell, char *key, char *value, int visible);
int		pwd_command(t_shell *shell, t_exec_node *cmd);
void	export_command(t_shell *shell, t_exec_node *cmd);
void	unset_command(t_shell *shell, t_exec_node *cmd);
void	exit_command(t_shell *shell, t_exec_node *cmd);
int		error_in(t_shell *shell, char *cmd, char *arg, int error_code);
void	envp_update(t_shell *shell);
void	envp_sort(t_shell *shell);
void	envp_to_list(char **envp, t_shell *shell);
char	*env_get(char *key, t_shell *shell);
bool	env_rm(char *key, t_shell *shell);
void	run_cmd(t_shell *shell, t_cmd *cmd);
void	expand_arg(t_shell *shell, char **arg);
void	trim_quotes(char *arg, int *len);
int		expand(char *key, int i, int j, char **line);
int		check_fork(void);
void	run_cmd(t_shell *shell, t_cmd *cmd);
void	run_exec(t_shell *shell, t_exec_node *cmd);
void	free_exit(t_shell *shell);
void	run_heredoc(t_shell *shell, t_here *here);
int		check_error_and_exit(int result, char *msg, int exit_code);
int		check_fork(void);
void	wait_children(t_shell *shell);
void	run_redir(t_shell *shell, t_redir_node *cmd);
void	trim_arg(char *arg);
int		expand_free(char *key, int i, int j, char **line);
void	expand_wildcard(char **line);
char	**convert_tokens_to_argv(t_token **tokens);
void	check_exit_status(void);
void	expand_argv(t_shell *shell, t_token **tokens_argv);

#endif
