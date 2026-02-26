/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 10:56:36 by jdelmott          #+#    #+#             */
/*   Updated: 2026/02/26 15:30:47 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <sys/wait.h>

typedef struct s_command
{
	char	**s_cmd;
	int		free;
}			t_command;

typedef struct s_accessible
{
	char	**all_path;
	char	**s_cmd;
	char	*join;
	char	*path;
	int		i;
}			t_accessible;

//	PIPEX
char		*is_accessible(char *cmd, char *envp[]);
void		exec(char *cmd, char *envp[]);
int			open_file(char *fd_arg, int mode);
char		**split_pipex(char *str, const char sep);

//	PIPEX_BONUS
char		*gnl_pipex(int fd, char *arg);

#endif
