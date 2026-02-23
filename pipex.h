/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelmott <jdelmott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 10:56:36 by jdelmott          #+#    #+#             */
/*   Updated: 2026/02/23 10:30:11 by jdelmott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <sys/wait.h>

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

//	PIPEX_BONUS
char		*gnl_pipex(int fd, char *arg);

#endif
