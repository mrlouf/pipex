/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:55:07 by nponchon          #+#    #+#             */
/*   Updated: 2024/11/21 15:42:13 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

void	child_process(t_pipex *pipex)
{
	if (pipex->child == 0)
		redirect_fds(pipex->fd_infile, pipex->pipe[1]);
	else if (pipex->child == pipex->nb_cmds - 1)
		redirect_fds(pipex->pipe[2 * pipex->child - 2], pipex->fd_outfile);
	else
		redirect_fds(pipex->pipe[2 * pipex->child - 2],
			pipex->pipe[2 * pipex->child + 1]);
	close_allfds(pipex);
	if (access(pipex->filename[pipex->child], X_OK) == 0)
		execve(pipex->filename[pipex->child],
			pipex->commands[pipex->child], pipex->paths);
	pipex->exit_code = 127;
	message_error(pipex->commands[pipex->child][0], " : command not found");
	exit(pipex->exit_code);
}

void	close_allfds(t_pipex *pipex)
{
	int	i;

	if (pipex->fd_infile != -1)
		close(pipex->fd_infile);
	if (pipex->fd_outfile != -1)
		close(pipex->fd_outfile);
	i = 0;
	while (i < (pipex->nb_cmds - 1) * 2)
	{
		close(pipex->pipe[i]);
		i++;
	}
}

void	parent_process(t_pipex *pipex)
{
	int		status;

	close_allfds(pipex);
	pipex->child--;
	while (pipex->child >= 0)
	{
		waitpid(pipex->pids[pipex->child], &status, 0);
		pipex->child--;
	}
}

void	redirect_fds(int input, int output)
{
	if (dup2(input, STDIN_FILENO) == -1)
	{
		message_error("Infile: ", "No such file or directory");
		exit(errno);
	}
	close(input);
	if (dup2(output, STDOUT_FILENO) == -1)
		exit_error(errno);
	close(output);
}

void	execute_pipex(t_pipex *pipex)
{
	create_pipes(pipex);
	if (pipe(pipex->pipe) == -1)
		exit_error(errno);
	while (pipex->child < pipex->nb_cmds)
	{
		pipex->pids[pipex->child] = fork();
		if (pipex->pids[pipex->child] == -1)
			exit_error(errno);
		if (pipex->pids[pipex->child] == 0)
			child_process(pipex);
		pipex->child++;
	}
	parent_process(pipex);
}
