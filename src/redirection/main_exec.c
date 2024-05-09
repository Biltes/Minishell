/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:24:35 by migupere          #+#    #+#             */
/*   Updated: 2024/05/09 12:12:110 by pevieira         ###   ########.fr       */
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
    g_exit = 127
        - ((!access(path, F_OK) && access(path, X_OK)) || !access(path, F_OK));
    free(path);
    free_exit(shell);
}

static char	*get_path(t_shell *sh, char *cmd)
{
    int		i;
    char	*path;
    char	*path2;
    char	**paths;

    i = 0;
    path = NULL;
    path2 = NULL;
    if (ft_strchr("/.", cmd[0]) || !env_get("PATH", sh) || !ft_strcmp(cmd, ""))
        return (ft_strdup(cmd));
    paths = ft_split(env_get("PATH", sh), ':');
    while (paths[i])
    {
        path = ft_strjoin(paths[i], "/");
        path2 = ft_strjoin(path, cmd);
        free(path);
        path = NULL;
        if (!access(path2, F_OK))
            return (path2);
        free(path2);
        path2 = NULL;
        i++;
    }
    free_array(paths);
    return (ft_strdup(cmd));
}

static void	check_exit_status(void)
{
    if (g_exit == SEGFAULT || g_exit == SEGFAULT_COREDUMPED)
        ft_putendl_fd("Segmentation fault (core dumped)", STDERR_FILENO);
    else if (g_exit == FLOAT_EXCEPTION || g_exit == FLOAT_EXCEPTION_COREDUMPED)
        ft_putendl_fd("Floating point exception (core dumped)", STDERR_FILENO);
}

static void	expand_argv(t_shell *shell, t_token **tokens_argv)
{
    int		len;
    int		i;
    int		expanded;
    char	*tmp;

    if (!tokens_argv[0]->value)
        return ;
    expanded = (ft_strchr(tokens_argv[0]->value, '$') || ft_strchr(tokens_argv[0]->value, '*'));
    expand_arg(shell, &tokens_argv[0]->value);
    len = ft_strlen(tokens_argv[0]->value);
    trim_arg(tokens_argv[0]->value);
    trim_quotes(tokens_argv[0]->value, &len);
    i = 1;
    tmp = tokens_argv[0]->value;
    while ((tmp < tokens_argv[0]->value + len) && i < (MAXARG - 1))
    {
        if (*tmp == '\0' && (ft_strcmp(tokens_argv[0]->value, "printf") || i != 2))
            tokens_argv[i++]->value = tmp + 1;
        tmp++;
    }
    if (!tokens_argv[0]->value[0] && expanded)
    {
        free(tokens_argv[0]->value);
        tokens_argv[0]->value = NULL;
    }
}

void	run_exec(t_shell *shell, t_exec_node *cmd)
{
    pid_t	pid;
    char	*path;
    char    **argv;

    expand_argv(shell, cmd->tokens_argv);
    if (!cmd->tokens_argv[0]->value)
        return (g_exit = 0, (void)0);
    if (run_builtin(shell, cmd))
        return ;
    signals_set(SIGCHILD, shell);
    pid = check_fork();
    if (pid == 0)
    {
        path = get_path(shell, cmd->tokens_argv[0]->value);
        argv = convert_tokens_to_argv(cmd->tokens_argv);
        execve(path, argv, shell->envp);
        free(argv);
        check_execve(shell, path);
    }
    waitpid(pid, &g_exit, 0);
    if (WIFEXITED(g_exit))
        g_exit = WEXITSTATUS(g_exit);
    else if (WIFSIGNALED(g_exit))
        g_exit = EXIT_SIG_OFFSET + WTERMSIG(g_exit);
    check_exit_status();
    signals_set(RESTORE, shell);
}
