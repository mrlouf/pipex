/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:55:07 by nponchon          #+#    #+#             */
/*   Updated: 2024/11/15 14:37:37 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

void	child_process(t_pipex *pipex, int *end)
{
	dup2(pipex->fd_infile, STDIN_FILENO);
	close(pipex->fd_infile);
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	execve("/usr/bin/grep", pipex->commands[0], NULL);
	write(2, "Child failed\n", 13);
	exit(EXIT_FAILURE);
}

void	parent_process(t_pipex *pipex, int *end)
{
	dup2(pipex->fd_outfile, 1);
	close(pipex->fd_outfile);
	dup2(end[0], 0);
	close(end[1]);
	execve("/usr/bin/wc", pipex->commands[1], NULL);
	write(2, "Parent failed\n", 14);
	exit(EXIT_FAILURE);
}

void	execute_pipex(t_pipex *pipex)
{
	int		end[2];
	pid_t	pid;

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
