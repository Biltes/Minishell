/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:50:20 by migupere          #+#    #+#             */
/*   Updated: 2024/07/18 15:56:42 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	check_execve(t_shell *shell, char *path)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	if (!access(path, F_OK) && access(path, X_OK) && ft_strchr(path, '/'))
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	else if (!access(path, F_OK) && !access(path, X_OK) && path[0] != '.')
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
	else if (ft_strchr(path, '/') || !env_get("PATH", shell))
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	else
		ft_putendl_fd(": command not found", STDERR_FILENO);
	g_exit = 127 - !access(path, F_OK);
	free(path);
	free_exit(shell);
}

static char	*get_path(t_shell *sh, char *cmd, int i)
{
	char	*path;
	char	*path2;
	char	**paths;

	path = NULL;
	path2 = NULL;
	if (!sh->env)
		sh->env = env_add_or_mod(sh, "PATH", cmd, 1);
	if (ft_strchr("/.", cmd[0]) || !env_get("PATH", sh) || !ft_strcmp(cmd, ""))
		return (ft_strdup(cmd));
	paths = ft_split(env_get("PATH", sh), ':');
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		path2 = ft_strjoin(path, cmd);
		free(path);
		if (!access(path2, F_OK))
		{
			free_array(paths);
			return (path2);
		}
		free(path2);
	}
	free_array(paths);
	return (ft_strdup(cmd));
}

void	run_exec(t_shell *shell, t_exec_node *cmd)
{
	pid_t	pid;
	char	*path;
	char	**argv;

	expand_argv(shell, cmd->tokens_argv);
	if ((!cmd->tokens_argv[0]) || (!cmd->tokens_argv[0]->value))
		return (g_exit = 0, (void)0);
	if (run_builtin(shell, cmd))
		return ;
	signals_set(SIGCHILD, shell);
	pid = check_fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		path = get_path(shell, cmd->tokens_argv[0]->value, -1);
		argv = convert_tokens_to_argv(cmd->tokens_argv);
		execve(path, argv, shell->envp);
		free(argv);
		check_execve(shell, path);
	}
	waitpid(pid, &g_exit, 0);
	check_exit_status();
	signals_set(RESTORE, shell);
}

void	check_exit_status(void)
{
	if (WIFEXITED(g_exit))
		g_exit = WEXITSTATUS(g_exit);
	else if (WIFSIGNALED(g_exit))
		g_exit = EXIT_SIG_OFFSET + WTERMSIG(g_exit);
	if (g_exit == SEGFAULT || g_exit == SEGFAULT_COREDUMPED)
		ft_putendl_fd("Segmentation fault (core dumped)", STDERR_FILENO);
	else if (g_exit == FLOAT_EXCEPTION || g_exit == FLOAT_EXCEPTION_COREDUMPED)
		ft_putendl_fd("Floating point exception (core dumped)", STDERR_FILENO);
}

void	executor(t_shell *m_shell)
{
	if (m_shell->ast)
		run_cmd(m_shell, m_shell->ast);
}
