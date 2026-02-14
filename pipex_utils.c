/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 09:12:52 by jdelmott          #+#    #+#             */
/*   Updated: 2026/02/14 13:01:15 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *fd_arg, int mode)
{
	int	fd;

	if (mode == 0)
	{
		fd = open(fd_arg, O_RDONLY, 0777);
		if (fd == -1)
		{
			ft_printf_fd(2, "pipex: %s: Permission denied\n", fd_arg);
			exit(0);
		}
	}
	else
	{
		fd = open(fd_arg, O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (fd == -1)
		{
			ft_printf_fd(2, "pipex: %s: Permission denied\n", fd_arg);
			exit(2);
		}
	}
	return (fd);
}

char	*is_already_path(char *cmd)
{
	char	*path;

	if (access(cmd, X_OK | F_OK) == 0)
		return (cmd);
	path = ft_strjoin("/", cmd);
	if (access(path, X_OK | F_OK) == 0)
		return (path);
	free(path);
	return (NULL);
}

void	exec(char *cmd, char *envp[])
{
	char	*path;
	char	**s_cmd;

	s_cmd = ft_split(cmd, ' ');
	path = is_already_path(cmd);
	if (path == NULL)
	{
		free(path);
		path = is_accessible(s_cmd[0], envp);
	}
	if (execve(path, s_cmd, envp) == -1)
	{
		free_tab(s_cmd);
		ft_printf_fd(2, "pipex: command not found: %s\n", cmd);
		exit(127);
	}
	free_tab(s_cmd);
	free(path);
}

char	*is_accessible(char *cmd, char *envp[])
{
	t_accessible	temp;

	temp.i = 0;
	temp.all_path = ft_split(ft_getenv("PATH", envp), ':');
	temp.s_cmd = ft_split(cmd, ' ');
	while (temp.all_path[temp.i])
	{
		temp.join = ft_strjoin(temp.all_path[temp.i], "/");
		temp.path = ft_strjoin(temp.join, temp.s_cmd[0]);
		if (access(temp.path, X_OK | F_OK) == 0)
		{
			free(temp.join);
			free_tab(temp.all_path);
			free_tab(temp.s_cmd);
			return (temp.path);
		}
		free(temp.join);
		free(temp.path);
		temp.i++;
	}
	free_tab(temp.s_cmd);
	free_tab(temp.all_path);
	return (cmd);
}
