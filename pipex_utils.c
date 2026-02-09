/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 09:12:52 by jdelmott          #+#    #+#             */
/*   Updated: 2026/02/09 17:59:12 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*is_already_path(char *cmd, char *envp[])
{
	if (access(cmd, X_OK | F_OK) == 0)
		return (cmd);
	return (NULL);
}

void	exec(char *cmd, char *envp[])
{
	char	*path;
	char	**s_cmd;

	s_cmd = ft_split(cmd, ' ');
	path = is_accessible(s_cmd[0], envp);
	if (execve(path, s_cmd, envp) == -1)
	{
		
		free_tab(s_cmd);
		ft_putendl_fd("Error\nnot a valid command", 2);
		exit(-1);
	}
	free_tab(s_cmd);
	free(path);
}

char	*is_accessible(char *cmd, char *envp[])
{
	char	**all_path;
	char	**s_cmd;
	char	*join;
	char	*path;
	int		i;

	i = 0;
	if (is_already_path(cmd, envp))
		return (cmd);
	all_path = ft_split(ft_getenv("PATH", envp), ':');
	s_cmd = ft_split(cmd, ' ');
	while (all_path[i])
	{
		join = ft_strjoin(all_path[i], "/");
		path = ft_strjoin(join, s_cmd[0]);
		if (access(path, X_OK | F_OK) == 0)
		{
			free(join);
			free_tab(all_path);
			free_tab(s_cmd);
			return (path);
		}
		free(join);
		free(path);
		i++;
	}
	free_tab(s_cmd);
	free_tab(all_path);
	return (cmd);
}
