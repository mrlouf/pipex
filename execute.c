/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:55:07 by nponchon          #+#    #+#             */
/*   Updated: 2024/11/19 17:46:42 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

void	child_process(t_pipex *pipex, int *end)
{
	close(end[0]);
	dup2(end[1], STDOUT_FILENO);
	close(end[1]);
	if (access(pipex->filename[0], X_OK) == 0 && pipex->is_invalidinfile == -1)
		execve(pipex->filename[0], pipex->commands[0], pipex->paths);
	errno = 2;
	if (pipex->is_invalidinfile == 0)
	{
		perror("infile");
		exit(EXIT_FAILURE);
	}
	perror("command");
	exit(EXIT_FAILURE);
}

void	parent_process(t_pipex *pipex, int *end)
{
	int	status;

	waitpid(-1, &status, 0);
	close(end[1]);
	dup2(end[0], STDIN_FILENO);
	close(end[0]);
	if (pipex->is_heredoc == 1)
		unlink(".heredoc.tmp");
	if (access(pipex->filename[1], X_OK) == 0)
		execve(pipex->filename[1], pipex->commands[1], pipex->paths);
	if (pipex->is_invalidinfile != 0)
	{
		errno = 2;
		perror("Command not found");
		exit(EXIT_FAILURE);
	}
}

void	execute_pipex(t_pipex *pipex)
{
	int		end[2];
	pid_t	pid;

	dup2(pipex->fd_infile, STDIN_FILENO);
	close(pipex->fd_infile);
	dup2(pipex->fd_outfile, STDOUT_FILENO);
	close(pipex->fd_outfile);
	if (pipe(end) == -1)
		print_error(errno);
	pid = fork();
	if (pid == -1)
		print_error(errno);
	if (pid == 0)
		child_process(pipex, end);
	else
		parent_process(pipex, end);
}
