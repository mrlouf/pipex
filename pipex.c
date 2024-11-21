/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:49:37 by nponchon          #+#    #+#             */
/*   Updated: 2024/11/21 15:47:06 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

void	get_heredoc(t_pipex *pipex)
{
	int		fd_in;
	int		fd_out;
	char	*line;

	fd_out = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	fd_in = dup(STDIN_FILENO);
	if (fd_in < 0 || fd_out < 0)
		exit_error(errno);
	line = NULL;
	ft_putstr_fd("here_doc>", 1);
	line = get_next_line(fd_in);
	while (line)
	{
		if (ft_strlen(pipex->args[1]) + 1 == ft_strlen(line)
			&& !ft_strncmp(line, pipex->args[1], ft_strlen(pipex->args[1] + 1)))
			close(fd_in);
		else
			ft_putstr_fd(line, fd_out);
		free(line);
		line = NULL;
		ft_putstr_fd("here_doc>", 1);
		line = get_next_line(fd_in);
	}
	close(fd_out);
}

void	open_files(t_pipex *pipex)
{
	if (ft_strncmp(pipex->args[0], "here_doc", 9) == 0)
		pipex->is_heredoc = 1;
	if (pipex->is_heredoc == 1)
	{
		get_heredoc(pipex);
		pipex->fd_infile = open(".heredoc.tmp", O_RDONLY, 0644);
		pipex->nb_cmds = pipex->ac - 4;
	}
	else
		pipex->fd_infile = open(pipex->args[0], O_RDONLY);
	if (pipex->fd_infile < 0)
	{
		pipex->is_invalidinfile = 1;
		pipex->exit_code = 1;
	}
	if (pipex->is_heredoc == 1)
		pipex->fd_outfile = open(pipex->args[pipex->nb_cmds + 2], \
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		pipex->fd_outfile = open(pipex->args[pipex->nb_cmds + 1], \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd_outfile < 0)
		exit_error(EACCES);
}

void	create_pipes(t_pipex *pipex)
{
	int	i;

	i = -1;
	pipex->pids = malloc(sizeof(int *) * pipex->nb_cmds);
	if (!pipex->pids)
		exit_error(errno);
	pipex->pipe = malloc(sizeof(int *) * 2 * (pipex->nb_cmds - 1));
	if (!pipex->pipe)
		exit_error(errno);
	while (++i < pipex->nb_cmds - 1)
	{
		if (pipe(pipex->pipe + 2 * i) == -1)
			exit_error(errno);
	}
}

void	init_pipex(t_pipex *pipex, int ac, char **av, char **envp)
{
	if (ac < 5)
		exit_error(EINVAL);
	pipex->fd_infile = -1;
	pipex->fd_outfile = -1;
	pipex->is_heredoc = 0;
	pipex->is_invalidinfile = -1;
	pipex->ac = ac;
	pipex->nb_cmds = ac - 3;
	pipex->paths = envp;
	pipex->args = av + 1;
	pipex->child = 0;
	pipex->pipe = 0;
	pipex->pids = 0;
	pipex->exit_code = 0;
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	init_pipex(&pipex, ac, av, envp);
	open_files(&pipex);
	check_parameters(&pipex);
	execute_pipex(&pipex);
	clean_pipex(&pipex);
	return (pipex.exit_code);
}
