/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 11:04:36 by jdelmott          #+#    #+#             */
/*   Updated: 2026/02/09 12:22:08 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_proc(int f1, char *comd1, int end_pipe[2], char *envp[])
{
	dup2(f1, STDIN_FILENO);
	dup2(end_pipe[1], STDOUT_FILENO);
	close(end_pipe[0]);
	close(f1);
	exec(comd1, envp);
}

void	parent_proc(int f2, char *comd2, int end_pipe[2], char *envp[])
{
	int	status;

	// waitpid(-1, &status, 0);
	wait(&status);
	dup2(f2, STDOUT_FILENO);
	dup2(end_pipe[0], STDIN_FILENO);
	close(end_pipe[1]);
	close(f2);
	exec(comd2, envp);
}

void	pipex(int f1, int f2, char *argv[], char *envp[])
{
	int		end_pipe[2];
	pid_t	parent;

	pipe(end_pipe);
	parent = fork();
	if (parent == -1)
		exit(-1);
	if (parent < 0)
		return (perror("FORK: ")); // a revoir
	if (!parent)
		child_proc(f1, argv[2], end_pipe, envp);
	else
		parent_proc(f2, argv[3], end_pipe, envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	f1;
	int	f2;
	
    if (argc != 5)
		return (1);
	f1 = open(argv[1], O_RDONLY);
	if (f1 == -1)
		return (1);
	f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC);
    if (f2 == -1)
        return (1);
    pipex(f1, f2, argv, envp);
	return (0);
}
