/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:49:37 by nponchon          #+#    #+#             */
/*   Updated: 2024/11/12 16:34:57 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

void    print_error(int err)
{
    errno = err;
    perror("Error");
    exit(EXIT_FAILURE);
}

void    free_array(void **array)
{
    int i;

    if (array == NULL)
        return ;
    i = -1;
    while (array[++i])
        free(array[i]);
    free(array);
    array = NULL;
}