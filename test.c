/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:37:38 by nponchon          #+#    #+#             */
/*   Updated: 2024/11/14 18:27:17 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int ac, char **av, char *env[])
{
	int		fd_in;
	int		fd_out;
	pid_t	pid;
	int		fdpipe[2];
	char	*args1[] = {"grep", "Lorem", NULL};
	char	*args2[] = {"wc", "-w", NULL};

	fd_in = open("infile", O_RDONLY);
	fd_out = open("outfile", O_WRONLY);
	if (fd_in < 0 || fd_out < 0)
		return (EXIT_FAILURE);
	pipe(fdpipe);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd_in, 0);
		close(fd_in);
		dup2(fdpipe[1], 1);
		close(fdpipe[0]);
		execve("/usr/bin/grep", args1, NULL);
		write(2, "Child failed\n", 14);
		exit(EXIT_FAILURE);
	}
	else
	{
		dup2(fd_out, 1);
		close(fd_out);
		dup2(fdpipe[0], 0);
		close(fdpipe[1]);
		execve("/usr/bin/wc", args2, NULL);
		write(2, "Parent failed\n", 14);
		exit(EXIT_FAILURE);
	}
}
