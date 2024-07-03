/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:24:50 by migupere          #+#    #+#             */
/*   Updated: 2024/07/03 14:51:35 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	expand_file_mane(t_shell *shell, char **file)
{
	int	len;

	if (ft_strchr(*file, '$') && ft_strchr(*file, '*'))
	{
		print_error(shell, *file, "Ambiguous Redirect", 1);
		return (0);
	}
	expand_arg(shell, file);
	len = ft_strlen(*file);
	trim_arg(*file);
	trim_quotes(*file, &len);
	return (1);
}

void	run_redir(t_shell *shell, t_redir_node *cmd)
{
	int	fd;
	int	original_fd;

	original_fd = dup(cmd->fd);
	if (original_fd == -1)
		return ;
	fd = -2;
	if (expand_file_mane(shell, &cmd->file))
	{
		fd = open(cmd->file, cmd->mode, FILE_PERMISSIONS);
		if (fd == -1)
		{
			print_error(shell, cmd->file, strerror(errno), 1);
			return ;
		}
	}
	if (fd != -1 && shell->status == CONTINUE)
	{
		if (dup2(fd, cmd->fd) == -1)
		{
			close(fd);
			return ;
		}
		close(fd);
		run_cmd(shell, cmd->cmd);
	}
	if (dup2(original_fd, cmd->fd) == -1)
		return ;
	close(original_fd);
}
