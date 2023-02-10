/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:40:29 by arakhurs          #+#    #+#             */
/*   Updated: 2023/02/10 17:13:26 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

double	pov(char c)
{
	if (c == 'N')
		return (90.0);
	if (c == 'S')
		return (270.0);
	if (c == 'E')
		return (0.0);
	if (c == 'W')
		return (180.0);
	return (0.0);
}

double	degree_to_radians(double a)
{
	return (a * (PI / 180));
}

double	ft_fabs(double a)
{
	return (a < 0 ? -a : a);
}

void	decreament_in_range(double range, double step, double *num)
{
	if (/*(int)*/(*num) - step >= 0)
		*num -= step;
	else
		*num = *num + range - step;
}

void	increament_in_range(double range, double step, double *num)
{
	if ((int)(*num) + step <= range)
		*num += step;
	else
		*num = *num - range + step;
}

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

int	is_odd_wall(double	intercept)
{
	return ((int)(intercept / (double)Field) % 2);
}

void	field_len(double intercept, t_component *comp, int img_height, int flag)
{
	double	tmp;

	if (is_odd_wall(intercept))
		tmp = intercept - ((int)(intercept / Field) * Field);
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
