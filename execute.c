/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:55:07 by nponchon          #+#    #+#             */
/*   Updated: 2024/11/14 15:28:53 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

void	execute_pipex(t_pipex *pipex, int i)
{
	int		fd[2];
	pid_t	pid;
	char	*args1 = {"Lorem", NULL};
	char	*args2 = {"-w", NULL};

	if (pipe(fd) == -1)
		print_error(errno);
	pid = fork();
	if (pid == -1)
		print_error(errno);
	if (pid == 0)
	{
		close(fd[READ_END]);
		execve("grep", args1, pipex->cmd_paths);
		close(fd[WRITE_END]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[WRITE_END]);
		wait(NULL);
		read(fd[READ_END], buffer, 13);
		close(fd[READ_END]);
		execve("wc", args2, pipex->cmd_paths);
		exit(EXIT_SUCCESS);
	}
}
