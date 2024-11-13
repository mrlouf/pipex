/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:50:10 by nponchon          #+#    #+#             */
/*   Updated: 2024/11/12 16:30:39 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include "libft/libft.h"

# define READ_END   0
# define WRITE_END  1

typedef struct s_pipex
{
    int     fd_infile;
    int     fd_outfile;
    int     argc;
    int     is_heredoc;
    int     is_invalidinfile;
    char    **argv;
    char    **cmd_paths;
}   t_pipex;

void    init_pipex(t_pipex *pipex, int ac, char **av, char **envp);
char	**find_cmdpaths(char **envp);
void	check_parameters(t_pipex *pipex);

//  ERRORS AND FREES
void    print_error(int err);
void    free_array(void **array);

#endif