/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:50:10 by nponchon          #+#    #+#             */
/*   Updated: 2024/11/19 14:25:35 by nponchon         ###   ########.fr       */
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
	int		is_heredoc;
	int		is_invalidinfile;
	int		ac;
	int		nb_cmds;
	char	**args;
	char	***commands;
	char	**paths;
	char	**filename;
}	t_pipex;

//  INITIALISATION AND CHECKS
void	init_pipex(t_pipex *pipex, int ac, char **av, char **envp);
void	open_files(t_pipex *pipex);
void	get_paths(t_pipex *pipex);
void	check_parameters(t_pipex *pipex);

//	EXECUTING PIPES
void	execute_pipex(t_pipex *pipex);
void	child_process(t_pipex *pipex, int *end);
void	parent_process(t_pipex *pipex, int *end);

//	HEREDOC
void	get_heredoc(t_pipex *pipex);

//  ERRORS, FREES & DEBUG
void	clean_pipex(t_pipex *pipex);
void	print_error(int err);
void	free_array(void **array);
void	close_fds(int fd1, int fd2);

//	UTILS & DEBUG
void	print_array(char **array);
char	*copy_path_cmd(const char *s1, const char *s2);

#endif
