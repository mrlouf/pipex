/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:49:37 by nponchon          #+#    #+#             */
/*   Updated: 2024/11/14 12:53:32 by nponchon         ###   ########.fr       */
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
	printf("i=%d\n", i);
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

	i = -1;
	close_fds(pipex->fd_infile, pipex->fd_outfile);
	while (++i < pipex->nb_cmds)
	{
		free_array((void **)pipex->cmd_paths[i]);
	}
}
