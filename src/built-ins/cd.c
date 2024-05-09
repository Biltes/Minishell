/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migupere <migupere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:32:52 by migupere          #+#    #+#             */
/*   Updated: 2024/05/06 16:30:17 by migupere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*path_slash(char *cdpath, char **path)
{
	char	*tmp;

	if (cdpath[ft_strlen(cdpath) - 1] != '/')
	{
		if (*path[0] != '/')
		{
			tmp = ft_strjoin("/", *path);
			return (tmp);
		}
		else
			return (ft_strdup(cdpath));
	}
	else
	{
		if (*path[0] == '/')
		{
			tmp = ft_strdup(*path + 1);
			return (tmp);
		}
		else
			return (ft_strdup(cdpath));
	}
}

static bool	cdpath_try(t_shell *shell, char **cdpath, char *path, int index)
{
	char	*tmp;
	char	*tmp_path;

	tmp_path = path_slash(cdpath[index], &path);
	tmp = ft_strjoin(cdpath[index], tmp_path);
	free(tmp_path);
	if (chdir_command(shell, tmp))
	{
		tmp[ft_strlen(tmp) - 1] = '\0';
		ft_putendl_fd(tmp, STDOUT_FILENO);
		free_array(cdpath);
		free(tmp);
		return (true);
	}
	free(tmp);
	return (false);
}

static bool	cdpath(t_shell *shell, char *path)
{
	char	**cdpath;
	int		i;

	if (!env_get("CDPATH", shell) || path[0] == '/')
		return (false);
	cdpath = ft_split(env_get("CDPATH", shell), ':');
	i = 0;
	while (cdpath[i])
	{
		if (cdpath_try(shell, cdpath, path, i++))
			return (true);
	}
	free_array(cdpath);
	return (false);
}

static void	hyphen_cd_print(t_shell *shell, char *pwd)
{
	char	*str;

	if (pwd[0] != '~')
		ft_putendl_fd(pwd, STDOUT_FILENO);
	else
	{
		str = ft_strjoin(env_get("HOME", shell), &pwd[1]);
		ft_putendl_fd(str, STDOUT_FILENO);
		free(str);
	}
}

void	cd_command(t_shell *shell, t_exec *cmd)
{
	if (!cmd->argv[1] || !*cmd->argv[1])
	{
		if (!chdir_command(shell, env_get("HOME", shell)))
			print_error(shell, "cd", "HOME not set", 1);
	}
	else
	{
		if (cmd->argv[2])
			print_error(shell, "cd", "too many arguments", 1);
		else if (ft_strcmp(cmd->argv[1], "-") == 0)
		{
			if (!chdir_command(shell, env_get("OLDPWD", shell)))
			{
				print_error(shell, "cd", "OLDPWD not set", 1);
				return ;
			}
			hyphen_cd_print(shell, env_get("PWD", shell));
		}
		else if (cmd->argv[1][0]
			&& !chdir_command(shell, cmd->argv[1]) && !cdpath(shell, cmd->argv[1]))
			print_error(shell, "cd: no such file or directory",
				cmd->argv[1], 1);
	}
	if (shell->status == CONTINUE)
		g_exit = 0;
}
