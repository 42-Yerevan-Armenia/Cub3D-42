/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:33:16 by arakhurs          #+#    #+#             */
/*   Updated: 2023/02/14 18:08:51 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	ft_to_integer(t_component *comp, int x, int y, int angle)
{
	if (x != -1)
	{
		if (angle >= 90 && angle <= 270)
			comp->x_int_wall = x - 1;
		else
			comp->x_int_wall = x + 1;
	}
	if (y != -1)
	{
		if (angle >= 0 && angle <= 180)
			comp->y_int_wall = y - 1;
		else
			comp->y_int_wall = y + 1;
	}
}

int	is_odd_wall(double intercept)
{
	return ((int)(intercept / (double)Field) % 2);
}

void	field_len(double intercept, t_component *comp, int img_height)
{
	double	tmp;

	if (is_odd_wall(intercept))
		tmp = intercept - (((int)(intercept / Field)) * Field);
	else
		tmp = (((int)(intercept / Field) + 1) * Field) - intercept;
	comp->pic_x = tmp * (double)((double)img_height / (double)Field);
	if ((int)comp->height_wall > Win_y)
	{
		comp->pic_y = (((double)(comp->height_wall) - (double)Win_y) \
		/ (double)2) * ((double)img_height / (double)comp->height_wall);
		comp->pic_y_step = (img_height - (comp->pic_y * 2)) / Win_y;
	}
	else
	{
		comp->pic_y = 0;
		comp->pic_y_step = (((double)img_height) / (comp->height_wall));
	}
}

int	get_color(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(int *)dst);
}
