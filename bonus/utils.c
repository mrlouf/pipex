/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:57:21 by nponchon          #+#    #+#             */
/*   Updated: 2024/11/19 15:07:00 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"
#include "../libft/libft.h"

/*	Custom ft_strjoin to append the filename to the path with necessary '/':
	"usr/bin" + "grep" = "usr/bin/grep"*/

char	*copy_path_cmd(const char *s1, const char *s2)
{
	char	*new;
	int		i;
	int		j;
	int		slash;

	slash = 0;
	if (s1[ft_strlen(s1) - 1] != 47)
		slash = 1;
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + slash + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	if (slash == 1)
		new[i++] = 47;
	j = 0;
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}

/*	Use ft_strnstr to find the string PATH in envp, then use split
	to get all command paths.	*/

void	get_paths(t_pipex *pipex)
{
	int		i;
	char	*tmp;
	char	**paths;

	paths = NULL;
	i = -1;
	while (pipex->paths[++i])
	{
		if (ft_strnstr(pipex->paths[i], "PATH", 4) != 0)
		{
			tmp = ft_strchr(pipex->paths[i], '=');
			paths = ft_split(tmp + 4, ':');
		}
	}
	pipex->paths = paths;
}

/*	Checks if the argument already is the complete path, if not look for it
	in the envp		*/

void	check_paths(t_pipex *pipex)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (pipex->commands[++i])
	{
		j = -1;
		while (pipex->paths[++j])
		{
			if (access(pipex->commands[i][0], X_OK) == 0)
			{
				pipex->filename[i] = pipex->commands[i][0];
				break ;
			}
			tmp = copy_path_cmd(pipex->paths[j], pipex->commands[i][0]);
			if (access(tmp, X_OK) == 0)
			{
				pipex->filename[i] = ft_strdup(tmp);
				free(tmp);
				break ;
			}
			free(tmp);
		}
	}
}

void	check_parameters(t_pipex *pipex)
{
	int	i;

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
	}
	pipex->filename = (char **)malloc(sizeof(char **) * (pipex->nb_cmds + 1));
	if (!pipex->filename)
		print_error(ENOMEM);
	pipex->filename[pipex->nb_cmds] = NULL;
	get_paths(pipex);
	check_paths(pipex);
}

void	get_heredoc(t_pipex *pipex)
{
	int		fd_in;
	int		fd_out;
	char	*line;

	fd_out = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	fd_in = dup(STDIN_FILENO);
	if (fd_in < 0 || fd_out < 0)
		print_error(errno);
	line = "";
	write(2, "cucufu\n", 7);
	while (1)
	{
		line = get_next_line(fd_in);
		if (line == NULL)
			break ;
		if (ft_strlen(pipex->args[1]) == ft_strlen(line)
			&& ft_strncmp(line, pipex->args[1], ft_strlen(pipex->args[1])) == 0)
			close(fd_out);
		else
			ft_putstr_fd(line, fd_out);
		free(line);
	}
	close(fd_out);
}
