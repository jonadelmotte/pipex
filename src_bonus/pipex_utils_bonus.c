/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 09:12:52 by jdelmott          #+#    #+#             */
/*   Updated: 2026/02/26 17:05:40 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *fd_arg, int mode)
{
	int	fd;

	if (mode == 0)
		fd = open(fd_arg, O_RDONLY, 0777);
	else if (mode == 1)
		fd = open(fd_arg, O_CREAT | O_RDWR | O_APPEND, 0777);
	else
		fd = open(fd_arg, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd == -1)
	{
		ft_printf_fd(2, "pipex: %s: Permission denied\n", fd_arg);
		if (mode == 0)
			exit(126);
		exit(1);
	}
	return (fd);
}

static int	no_fil_dir(t_command *command)
{
	char	**split;
	char	*path;

	split = ft_split(command->s_cmd[0], '/');
	if (ft_strcmp(split[0], "usr") == 0 && ft_strcmp(split[1], "bin") == 0)
	{
		if (access(command->s_cmd[0], X_OK | F_OK) != 0)
		{
			path = ft_strjoin("/", command->s_cmd[0]);
			if (access(path, X_OK | F_OK) != 0)
			{
				command->free = 1;
				free_tab(split);
				free(path);
				ft_printf_fd(2, "pipex: no such file or directory: %s\n",
					command->s_cmd[0]);
				return (127);
			}
		}
	}
	free_tab(split);
	return (0);
}

char	*is_already_path(t_command *command)
{
	char	*path;

	if (!*command->s_cmd)
		return (NULL);
	if (no_fil_dir(command) == 127)
		return (NULL);
	if (access(command->s_cmd[0], X_OK | F_OK) == 0)
		return (command->s_cmd[0]);
	path = ft_strjoin("/", command->s_cmd[0]);
	if (access(path, X_OK | F_OK) == 0)
		return (path);
	free(path);
	return (NULL);
}

void	exec(char *cmd, char *envp[])
{
	char		*path;
	t_command	command;

	if (!cmd[0])
		exit(1);
	command.free = 0;
	command.s_cmd = split_pipex(cmd, ' ');
	path = is_already_path(&command);
	if (command.s_cmd[0] == NULL)
	{
		free_tab(command.s_cmd);
		if (command.free == 0)
			ft_printf_fd(2, "pipex: command not found: \n");
		exit(127);
	}
	if (path == NULL)
		path = is_accessible(command.s_cmd[0], envp);
	if (execve(path, command.s_cmd, envp) == -1)
	{
		free_tab(command.s_cmd);
		if (command.free == 0)
			ft_printf_fd(2, "pipex: command not found: %s\n", cmd);
		exit(127);
	}
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
