/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:49:37 by nponchon          #+#    #+#             */
/*   Updated: 2024/11/21 14:58:02 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

void	exit_error(int err)
{
	errno = err;
	perror("Error");
	exit(EXIT_FAILURE);
}

void	message_error(char *cmd, char *str)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(str, 2);
}

void	free_filename(char **filename, int nb_filename)
{
	int	i;

	i = -1;
	while (++i < nb_filename)
		free(filename[i]);
	free(filename);
	filename = NULL;
}

void	close_fds(int fd1, int fd2)
{
	if (fd1 > 0)
		close(fd1);
	if (fd2 > 0)
		close(fd2);
}

void	clean_pipex(t_pipex *pipex)
{
	int	i;

	close_fds(pipex->fd_infile, pipex->fd_outfile);
	i = -1;
	if (pipex->commands == NULL)
		return ;
	while (++i < pipex->nb_cmds)
		free_array((void **)pipex->commands[i]);
	free(pipex->commands);
	pipex->commands = NULL;
	free_array((void **)pipex->paths);
	free_filename(pipex->filename, pipex->nb_cmds);
	free(pipex->pids);
	free(pipex->pipe);
	if (pipex->is_heredoc == 1)
		unlink(".heredoc.tmp");
}
