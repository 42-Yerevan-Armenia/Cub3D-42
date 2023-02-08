/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:22:29 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/06 14:22:43 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void draw_line(t_data *win_img_data, int x, int start_y, int end_y, int color)
{
	while (start_y < end_y)
	{
		my_mlx_pixel_put(win_img_data, x,  start_y, color);
		start_y++;
	}
}
