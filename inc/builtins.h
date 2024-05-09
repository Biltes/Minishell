/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migupere <migupere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:26:55 by migupere          #+#    #+#             */
/*   Updated: 2024/05/08 15:34:58 by migupere         ###   ########.fr       */
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

typedef struct s_exec
{
	int		type;
	char	*argv[MAXARG];
}			t_exec;

typedef struct s_command_block
{
    int		type;
    t_cmd	*cmd;
}			t_command_block;

void 	echo_command(t_exec *cmd);
int		run_builtin(t_shell *shell, t_exec *cmd);
void	cd_command(t_shell *shell, t_exec *cmd);
bool	chdir_command(t_shell *shell, char *path);
int		print_error(t_shell *shell, char *msg, char *msg2, int exit);
void	env_command(t_shell *shell, t_exec *cmd);
void 	envp_print(t_shell *shell);
void	env_export(t_shell *shell, char *key, char *value, int visible);
int		pwd_command(t_shell *shell, t_exec *cmd);
void	export_command(t_shell *shell, t_exec *cmd);
void 	unset_command(t_shell *shell, t_exec *cmd);
void	exit_command(t_shell *shell, t_exec *cmd);
int		error_in(t_shell *shell, char *cmd, char *arg, int error_code);
void	envp_update(t_shell *shell);
void	envp_sort(t_shell *shell);
void	envp_to_list(char **envp, t_shell *shell);
char	*env_get(char *key, t_shell *shell);
bool	env_rm(char *key, t_shell *shell);


#endif