/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:33:16 by arakhurs          #+#    #+#             */
/*   Updated: 2023/02/16 20:05:01 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static int	is_odd_wall(double intercept)
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
	if ((int)comp->height_wall >= Win_y)
	{
		comp->pic_y = (int)(((double)(comp->height_wall) - (double)Win_y) \
		/ (double)2) *((double)img_height / (double)comp->height_wall);
		comp->pic_y_step = ((img_height - ((comp->pic_y) * 2))) / (Win_y);
	}
	else
	{
		comp->pic_y = 0;
		comp->pic_y_step = ((img_height) / (comp->height_wall + 1));
	}
}

int	get_color(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(int *)dst);
}

void	adjust_tile_step(t_component *comp, double angle)
{
	if (angle >= 90 && angle <= 270)
		comp->tile_step_x = -1;
	else
		comp->tile_step_x = 1;
	if (angle >= 0 && angle <= 180)
		comp->tile_step_y = -1;
	else
		comp->tile_step_y = 1;
}

void	adjust_dx_dy(t_component *comp, double angle, double x, double y)
{
	if (angle >= 90 && angle <= 270)
		comp->dx = ft_fabs((((int)x / Field) * Field) - x);
	else
		comp->dx = ft_fabs((((((int)(x / Field)) * Field) + Field) - x));
	if (angle >= 0 && angle <= 180)
		comp->dy = ft_fabs((y - (((int)(y / Field)) * Field)));
	else
		comp->dy = ft_fabs((y - (((int)(y / Field)) * Field + Field)));
}
