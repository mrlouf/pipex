/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:50:10 by nponchon          #+#    #+#             */
/*   Updated: 2024/11/14 12:54:26 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include "libft/libft.h"

# define READ_END   0
# define WRITE_END  1

typedef struct s_pipex
{
	int		fd_infile;
	int		fd_outfile;
	int		nb_cmds;
	int		is_heredoc;
	int		is_invalidinfile;
	char	***commands;
	char	**cmd_paths;
}	t_pipex;

//  INITIALISATION AND CHECKS
void	init_pipex(t_pipex *pipex, int ac, char **av, char **envp);
char	**find_cmdpaths(char **envp);
void	check_parameters(t_pipex *pipex);

//	PIPES AND REDIRECTIONS
void	execute_pipex(t_pipex *pipex, int i);

//  ERRORS AND FREES
void	clean_pipex(t_pipex *pipex);
void	print_error(int err);
void	free_array(void **array);
void	close_fds(int fd1, int fd2);

#endif