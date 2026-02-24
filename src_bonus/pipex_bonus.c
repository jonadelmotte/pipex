/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:25:16 by jdelmott          #+#    #+#             */
/*   Updated: 2026/02/24 17:42:36 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc(char *argv[])
{
	int		end_pipe[2];
	pid_t	child;
	char	*gnl;
	char	*join;
	
	pipe(end_pipe);
	child = fork();
	if (!child)
	{		
		ft_printf_fd(2, "pipe heredoc> ");
		join = ft_strjoin(argv[2], "\n");
		gnl = gnl_pipex(0, join);
		close(end_pipe[0]);

		while (ft_strcmp(gnl, join) != 0)
		{
			ft_printf_fd(2, "pipe heredoc> ");
			ft_printf_fd(end_pipe[1], "%s", gnl);
			free(gnl);
			gnl = gnl_pipex(0, join);
		}
		free(join);
		free(gnl);
		exit(0);
	}
	else
	{
		wait(NULL);
		close(end_pipe[1]);
		dup2(end_pipe[0], 0);
	}
}

void	last_child(char *cmd, char *envp[], int outfile)
{
	pid_t	child;
	int		status;
	
	if (!cmd[0])
	{
		ft_printf_fd(2, "pipex: permission denied: \n");
		exit (127);
	}
	child = fork();
	if (!child)
	{
		dup2(outfile, 1);
		exec(cmd, envp);
	}
	else
	{
		waitpid(child, &status, 0);
		if (WIFEXITED(status))
			exit(WEXITSTATUS(status));
		exit(0);
	}
}

void	pipex_bonus(char *cmd, char *envp[])
{
	pid_t	child;
	int		end_pipe[2];

	if (!cmd[0])
	{
		ft_printf_fd(2, "pipex: permission denied: \n");
		exit (127);
	}
	pipe(end_pipe);
	child = fork();
	if (!child)
	{
		dup2(end_pipe[1], 1);
		close(end_pipe[0]);
		exec(cmd, envp);
	}
	else
	{
		dup2(end_pipe[0], 0);
		close(end_pipe[1]);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	size_t	i;
	int		fd_infile;
	int		fd_outfile;

	i = 2;
	if (argc < 4)
		return (1);
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		if (argc < 5)
			return (1);
		i = 3;
		fd_outfile = open_file(argv[argc - 1], 1);
		here_doc(argv);
	}
	else
	{
		fd_infile = open_file(argv[1], 0);
		fd_outfile = open_file(argv[argc - 1], 2);
		dup2(fd_infile, 0);
	}
	while (argv[i + 2] != NULL)
		pipex_bonus(argv[i++], envp);
	last_child(argv[i], envp, fd_outfile);
	//dup2(fd_outfile, 1);
	//exec(argv[i], envp);
}
