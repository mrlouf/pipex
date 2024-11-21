/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:49:37 by nponchon          #+#    #+#             */
/*   Updated: 2024/11/19 16:10:03 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
	{
		ft_printf("%s ", array[i]);
	}
	ft_printf("\n");
}