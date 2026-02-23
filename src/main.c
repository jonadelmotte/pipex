/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:25:16 by jdelmott          #+#    #+#             */
/*   Updated: 2026/02/23 11:40:31 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1_proc(char *file1, char *comd1, int end_pipe[2], char *envp[])
{
	int	fd;

	if (!comd1[0])
	{
		ft_printf_fd(2, "pipex: permission denied: \n");
		exit (127);
	}
	fd = open_file(file1, 0);
	dup2(fd, STDIN_FILENO);
	dup2(end_pipe[1], STDOUT_FILENO);
	close(end_pipe[0]);
	close(fd);
	exec(comd1, envp);
}

void	child2_proc(char *file2, char *comd2, int end_pipe[2], char *envp[])
{
	int	fd;

	if (!comd2[0])
	{
		ft_printf_fd(2, "pipex: permission denied \n");
		exit (127);
	}
	fd = open_file(file2, 1);
	dup2(fd, STDOUT_FILENO);
	dup2(end_pipe[0], STDIN_FILENO);
	close(end_pipe[1]);
	close(fd);
	exec(comd2, envp);
}

void	pipex(char *argv[], char *envp[])
{
	int		end_pipe[2];
	pid_t	parent;
	pid_t	parent2;
	int		status;
	int		status2;

	pipe(end_pipe);
	parent = fork();
	if (parent == -1)
		exit(-1);
	if (!parent)
		child1_proc(argv[1], argv[2], end_pipe, envp);
	parent2 = fork();
	if (!parent2)
		child2_proc(argv[4], argv[3], end_pipe, envp);
	close(end_pipe[0]);
	close(end_pipe[1]);
	waitpid(parent, &status, 0);
	waitpid(parent2, &status2, 0);
	if (WIFEXITED(status2))
		exit(WEXITSTATUS(status2));
	exit(0);
}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc != 5)
	{
		ft_printf_fd(2, "pipex: ./pipex infile cmd1 cmd2 outfile\n");
		return (1);
	}
	pipex(argv, envp);
	return (0);
}
