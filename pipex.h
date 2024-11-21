/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:50:10 by nponchon          #+#    #+#             */
/*   Updated: 2024/11/21 15:02:20 by nponchon         ###   ########.fr       */
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
	int		exit_code;
	int		fd_infile;
	int		fd_outfile;
	int		is_heredoc;
	int		is_invalidinfile;
	int		ac;
	int		nb_cmds;
	int		child;
	int		*pids;
	int		*pipe;
	char	**args;
	char	***commands;
	char	**paths;
	char	**filename;
}	t_pipex;

//  INITIALISATION AND CHECKS
void	init_pipex(t_pipex *pipex, int ac, char **av, char **envp);
void	open_files(t_pipex *pipex);
void	get_paths(t_pipex *pipex);
void	get_filename(t_pipex *pipex, int i, int j);
void	check_parameters(t_pipex *pipex);

//	EXECUTING PIPES
void	create_pipes(t_pipex *pipex);
void	execute_pipex(t_pipex *pipex);
void	redirect_fds(int input, int output);
void	child_process(t_pipex *pipex);
void	parent_process(t_pipex *pipex);
void	close_allfds(t_pipex *pipex);

//	HEREDOC
void	get_heredoc(t_pipex *pipex);

//  ERRORS, FREES & DEBUG
void	clean_pipex(t_pipex *pipex);
void	exit_error(int err);
void	message_error(char *cmd, char *str);
void	free_filename(char **filename, int nb_filename);
void	close_fds(int fd1, int fd2);

//	UTILS & DEBUG
char	*copy_path_cmd(const char *s1, const char *s2);

#endif
