/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_back.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:25:29 by vaghazar          #+#    #+#             */
/*   Updated: 2023/01/16 17:25:42 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void fill_back(void *mlx, void *mlx_win)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (i < Win_x)
	{
		while(j < Win_y / 2)
			mlx_pixel_put(mlx, mlx_win, i, j++, 0x00FF0000);
		i++;
		j = 0;
	}
	i = 0;
	j = Win_y / 2;
	while (i < Win_x)
	{
		while(j >= Win_y / 2 && j < Win_y)
			mlx_pixel_put(mlx, mlx_win, i, j++, 0x0000FF00);
		i++;
		j = Win_y / 2;
	}
}
