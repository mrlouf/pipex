/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:49:37 by nponchon          #+#    #+#             */
/*   Updated: 2024/11/15 14:02:53 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

/*	Use ft_strnstr to find the string PATH in envp, then use split
	to get all command paths.	*/

char	**find_cmdpaths(char **envp)
{
	int		i;
	char	*tmp;
	char	**paths;

	paths = NULL;
	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH", 4) != 0)
		{
			tmp = ft_strchr(envp[i], '=');
			paths = ft_split(tmp + 4, ':');
			return (paths);
		}
	}
	return (paths);
}

void	init_pipex(t_pipex *pipex, int ac, char **av, char **envp)
{
	if (ac < 4)
		print_error(EINVAL);
	pipex->fd_infile = open(av[1], O_RDONLY);
	pipex->fd_outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
	if (pipex->fd_infile < 0 || pipex->fd_outfile < 0)
		print_error(errno);
	/*if (ft_strnstr(av[1], "here_doc", 8) != 0)
		pipex->is_heredoc = 1;
	else
	*/
	pipex->is_heredoc = -1;
	pipex->is_invalidinfile = -1;
	pipex->nb_cmds = ac - 3;
	pipex->cmd_paths = envp;
	pipex->args = av + 1;
}

void	check_parameters(t_pipex *pipex)
{
	int	i;

	//pipex->cmd_paths = find_cmdpaths(pipex->cmd_paths);
	pipex->commands = (char ***)malloc(sizeof(char **) * (pipex->nb_cmds + 1));
	if (!pipex->commands)
		print_error(ENOMEM);
	pipex->commands[pipex->nb_cmds] = NULL;
	i = -1;
	while (++i < pipex->nb_cmds)
	{
		pipex->commands[i] = ft_split(pipex->args[i + 1], ' ');
		if (pipex->commands[i] == NULL)
			print_error(ENOMEM);
		print_array(pipex->commands[i]);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	init_pipex(&pipex, ac, av, envp);
	check_parameters(&pipex);
	execute_pipex(&pipex);
	clean_pipex(&pipex);
	return (EXIT_SUCCESS);
}
