/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migupere <migupere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:47:11 by migupere          #+#    #+#             */
/*   Updated: 2024/05/09 12:53:30 by migupere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int print_error_invalid_option(t_shell *shell, char *option)
{
    ft_putstr_fd("minishell: pwd: ", STDERR_FILENO);
    ft_putstr_fd(option, STDERR_FILENO);
    ft_putendl_fd(": invalid option", STDERR_FILENO);
    shell->status = 1;
    return (1);
}

static int print_error_getcwd(t_shell *shell)
{
    ft_putendl_fd("minishell: pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory", STDERR_FILENO);
    shell->status = 1;
    return (1);
}

static int handle_pwd(t_shell *shell, char *pwd)
{
    ft_putendl_fd(pwd, STDOUT_FILENO);
    free(pwd);
    shell->status = 0;
    return (0);
}

int	pwd_command(t_shell *shell, t_exec *cmd)
{
    char	*pwd;
    int		logical = 0;

    if (cmd->argv[1] && cmd->argv[1][0] == '-')
    {
        if (ft_strcmp(cmd->argv[1], "-L") == 0)
            logical = 1;
        else if (ft_strcmp(cmd->argv[1], "-P") != 0)
            return print_error_invalid_option(shell, cmd->argv[1]);
    }

    if (logical && shell->pwd)
        pwd = ft_strdup(shell->pwd);
    else
        pwd = getcwd(NULL, 0);

    if (!pwd)
        return print_error_getcwd(shell);

    return handle_pwd(shell, pwd);
}