/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:49:37 by nponchon          #+#    #+#             */
/*   Updated: 2024/11/12 16:34:57 by nponchon         ###   ########.fr       */
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
	if (ac <= 4)
		print_error(EINVAL);
	pipex->fd_infile = open(av[1], O_RDWR | O_CREAT);
	pipex->fd_outfile = open(av[ac - 1], O_RDWR | O_CREAT);
	if (pipex->fd_infile < 0 || pipex->fd_outfile < 0)
		print_error(EFAULT);
	pipex->is_heredoc = -1;
	pipex->is_invalidinfile = -1;
	pipex->argc = ac;
    pipex->argv = av + 1;
    pipex->cmd_paths = find_cmdpaths(envp);
}

void	check_parameters(t_pipex *pipex)
{
	printf("heredoc=%d\n", pipex->is_heredoc);
	if (ft_strnstr(pipex->argv[0], "here_doc", 8) != 0)
		pipex->is_heredoc = 1;
	printf("heredoc=%d\n", pipex->is_heredoc);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	init_pipex(&pipex, ac, av, envp);
	check_parameters(&pipex);
	/*parse_commands(&pipex);
	parse_arguments(&pipex);
	while (commands)
	{
		execute_pipex();
	}
	*/
	free_array((void **)&pipex.cmd_paths);
	return (EXIT_SUCCESS);
}