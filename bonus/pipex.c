/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:49:37 by nponchon          #+#    #+#             */
/*   Updated: 2024/11/19 15:10:01 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"
#include "../libft/libft.h"

void	open_files(t_pipex *pipex)
{
	if (ft_strncmp(pipex->args[0], "here_doc", 9) == 0)
		pipex->is_heredoc = 1;
	ft_printf("heredoc=%d\n", pipex->is_heredoc);
	if (pipex->is_heredoc == 1)
	{
		get_heredoc(pipex);
		pipex->fd_infile = open(".here.doc.tmp", O_RDONLY);
		pipex->nb_cmds = 2;
	}
	else
		pipex->fd_infile = open(pipex->args[0], O_RDONLY);
	if (pipex->fd_infile < 0)
		pipex->is_invalidinfile = 1;
	pipex->fd_outfile = open(pipex->args[pipex->nb_cmds + 1], \
			O_WRONLY | O_CREAT | O_TRUNC, 0);
	if (pipex->fd_outfile < 0)
		print_error(EACCES);
}

void	init_pipex(t_pipex *pipex, int ac, char **av, char **envp)
{
	if (ac < 5)
		print_error(EINVAL);
	pipex->is_invalidinfile = -1;
	pipex->fd_infile = -1;
	pipex->fd_outfile = -1;
	pipex->is_heredoc = -1;
	pipex->is_invalidinfile = -1;
	pipex->ac = ac;
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
	clean_pipex(&pipex);
	return (EXIT_SUCCESS);
}
