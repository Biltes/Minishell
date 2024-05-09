/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migupere <migupere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:24:50 by migupere          #+#    #+#             */
/*   Updated: 2024/05/09 15:32:52 by migupere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	expand_file_mane(t_shell *shell, char **file)
{
    int	len;

    if (ft_strchr(*file, '$') && ft_strchr(*file, '*'))
    {
        print_error(shell, *file, "ambiguous redirect", 1);
        return (0);
    }
    expand_arg(shell, file);
    len = ft_strlen(*file);
    trim_arg(*file);
    trim_quotes(*file, &len);
    free(*file); // Free file string
    return (1);
}

void	run_redir(t_shell *shell, t_redir_node *cmd)
{
    int		fd;
    int		original_fd;

    original_fd = dup(cmd->fd);
    fd = -2;
    if (expand_file_mane(shell, &cmd->file))
        fd = open(cmd->file, cmd->mode, FILE_PERMISSIONS);
    if (fd == -1)
        print_error(shell, cmd->file, strerror(errno), 1);
    else if (shell->status == CONTINUE)
    {
        dup2(fd, cmd->fd);
        close(fd);
        run_cmd(shell, cmd->cmd);
    }
    check_error_and_exit(dup2(original_fd, cmd->fd), "dup2 error", 1);
}
