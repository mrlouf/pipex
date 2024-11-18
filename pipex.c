/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:49:37 by nponchon          #+#    #+#             */
/*   Updated: 2024/11/18 17:19:35 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

void	init_pipex(t_pipex *pipex, int ac, char **av, char **envp)
{
	if (ac != 5)
		print_error(EINVAL);
	pipex->is_invalidinfile = -1;
	pipex->fd_infile = -1;
	pipex->fd_outfile = -1;
	pipex->is_heredoc = -1;
	if (ft_strnstr(av[1], "here_doc", 8) != 0)
		pipex->is_heredoc = 1;
	pipex->is_invalidinfile = -1;
	pipex->nb_cmds = ac - 3;
	pipex->paths = envp;
	pipex->args = av + 1;
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	init_pipex(&pipex, ac, av, envp);
	open_files(&pipex);
	check_parameters(&pipex);
	execute_pipex(&pipex);
	//clean_pipex(&pipex);
	return (EXIT_SUCCESS);
}
