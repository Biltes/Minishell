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
        {
            free_array(paths); // Free paths array
            return (path2);
        }
        free(path2);
        path2 = NULL;
        i++;
    }
    free_array(paths); // Free paths array
    return (ft_strdup(cmd));
}

static void	check_exit_status(void)
{
    if (g_exit == SEGFAULT || g_exit == SEGFAULT_COREDUMPED)
        ft_putendl_fd("Segmentation fault (core dumped)", STDERR_FILENO);
    else if (g_exit == FLOAT_EXCEPTION || g_exit == FLOAT_EXCEPTION_COREDUMPED)
        ft_putendl_fd("Floating point exception (core dumped)", STDERR_FILENO);
}

static void	expand_argv(t_shell *shell, char **argv)
{
    int		len;
    int		i;
    int		expanded;
    char	*tmp;

    if (!argv[0])
        return ;
    expanded = (ft_strchr(argv[0], '$') || ft_strchr(argv[0], '*'));
    expand_arg(shell, &argv[0]);
    len = ft_strlen(argv[0]);
    trim_arg(argv[0]);
    trim_quotes(argv[0], &len);
    i = 1;
    tmp = argv[0];
    while ((tmp < argv[0] + len) && i < (MAXARG - 1))
    {
        if (*tmp == '\0' && (ft_strcmp(argv[0], "printf") || i != 2))
            argv[i++] = tmp + 1;
        tmp++;
    }
    if (!argv[0][0] && expanded)
    {
        free(argv[0]);
        argv[0] = NULL;
    }
}

void	run_exec(t_shell *shell, t_exec_node *cmd)
{
    pid_t	pid;
    char	*path;
    printf("entrou1\n");
    expand_argv(shell, &cmd->tokens_argv[0]->value);
    printf("entrou8\n");
    if (!cmd->tokens_argv[0]->value)
        return (g_exit = 0, (void)0);
    if (run_builtin(shell, cmd))
        return ;
    signals_set(SIGCHILD, shell);
    pid = check_fork();
    if (pid == 0)
    {
        path = get_path(shell, cmd->tokens_argv[0]->value);
        execve(path, cmd->tokens_argv, shell->envp);
        printf("entrou4\n");
        check_execve(shell, path);
        printf("entrou777\n");
    }
    printf("entrou2\n");
    waitpid(pid, &g_exit, 0);
    if (WIFEXITED(g_exit))
        g_exit = WEXITSTATUS(g_exit);
    else if (WIFSIGNALED(g_exit))
        g_exit = 128 + WTERMSIG(g_exit);
    check_exit_status();
    printf("entrou6\n");
    signals_set(RESTORE, shell);
    printf("entrou77\n");
}
