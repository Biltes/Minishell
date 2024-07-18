/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:24:50 by migupere          #+#    #+#             */
/*   Updated: 2024/07/18 10:24:41 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	expand_name(t_shell *shell, char **file)
{
	int	len;

	if (ft_strchr(*file, '$') && ft_strchr(*file, '*'))
	{
		print_error(shell, *file, "Ambiguous Redirect", 1);
		return (0);
	}
	expand_arg(shell, file);
	len = ft_strlen(*file);
	trimming(*file, 0, 0);
	quotes_remove(*file, &len, 0, 0);
	return (1);
}

static int	open_redirect(t_shell *shell, t_redir_node *cmd, int *original_fd)
{
	int	fd;

	*original_fd = dup(cmd->fd);
	if (*original_fd == -1)
		return (-1);
	fd = -2;
	if (expand_name(shell, &cmd->file))
	{
		fd = open(cmd->file, cmd->mode, FILE_PERMISSIONS);
		if (fd == -1)
		{
			print_error(shell, cmd->file, strerror(errno), 1);
			return (-1);
		}
	}
	if (fd != -1 && shell->status == CONTINUE)
	{
		if (dup2(fd, cmd->fd) == -1)
		{
			close(fd);
			return (-1);
		}
		close(fd);
	}
	return (fd);
}

static void	exec_rst(t_shell *shell, t_redir_node *cmd, int original_fd, int fd)
{
	if (fd != -1 && shell->status == CONTINUE)
		run_cmd(shell, cmd->cmd);
	if (dup2(original_fd, cmd->fd) == -1)
	{
		close(original_fd);
		return ;
	}
	close(original_fd);
}

void	run_redir(t_shell *shell, t_redir_node *cmd)
{
	int	fd;
	int	original_fd;

	fd = open_redirect(shell, cmd, &original_fd);
	if (original_fd == -1 || fd == -1)
		return ;
	exec_rst(shell, cmd, original_fd, fd);
}
