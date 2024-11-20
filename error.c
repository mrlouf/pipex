/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:49:37 by nponchon          #+#    #+#             */
/*   Updated: 2024/11/19 16:10:03 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

//	TODO: function to unlink here_doc

void	print_error(int err)
{
	errno = err;
	perror("Error");
	exit(EXIT_FAILURE);
}

void	free_array(void **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
	array = NULL;
}

void	close_fds(int fd1, int fd2)
{
	close(fd1);
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
	free_array((void **)pipex->filename);
	free(pipex->pids);
	free(pipex->pipe);
	if (pipex->is_heredoc == 1)
		unlink(".heredoc.tmp");
}

void	print_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
	{
		ft_printf("%s ", array[i]);
	}
	ft_printf("\n");
}
