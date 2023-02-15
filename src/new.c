/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:22:29 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/15 21:19:11 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

double	get_dist_points(double p1_x, double p1_y, double p2_x, double p2_y)
{
	return (sqrt(ft_fabs((p1_x - p2_x) * (p1_x - p2_x))
			+ ft_fabs((p1_y - p2_y) * (p1_y - p2_y))));
}

int	check_hit_horiz(t_all *all)
{
	if (all->player.ray.angle >= 90 && all->player.ray.angle <= 270)
	{
		while ((all->comp.x_intercept > all->comp.x_int_wall * Field))
		{
			if (all->map.map[(int)all->comp.y_int_wall + all->comp.y_tile_wall] \
				[(int)all->comp.x_intercept / Field] != '0')
				return (HORIZ);
			all->comp.y_int_wall += all->comp.tile_step_y;
			all->comp.x_intercept += (all->comp.x_step * all->comp.tile_step_x);
		}
	}
	else
	{
		while (all->comp.x_intercept < all->comp.x_int_wall * Field)
		{
			if (all->map.map[(int)all->comp.y_int_wall + all->comp.y_tile_wall] \
				[(int)all->comp.x_intercept / Field] != '0')
				return (HORIZ);
			all->comp.y_int_wall += all->comp.tile_step_y;
			all->comp.x_intercept += (all->comp.x_step * all->comp.tile_step_x);
		}
	}
	return (0);
}

int	check_hit_vert(t_all *all)
{
	if (all->player.ray.angle >= 0 && all->player.ray.angle <= 180)
	{
		while ((all->comp.y_intercept > (all->comp.y_int_wall * Field)))
		{
			if (all->map.map[(int)all->comp.y_intercept / Field] \
				[(int)all->comp.x_int_wall + all->comp.x_tile_wall] != '0')
				return (VERT);
			all->comp.x_int_wall += all->comp.tile_step_x;
			all->comp.y_intercept += (all->comp.y_step * all->comp.tile_step_y);
		}
	}
	else
	{
		while ((all->comp.y_intercept < (all->comp.y_int_wall * Field)))
		{
			if (all->map.map[(int)all->comp.y_intercept / Field] \
				[(int)all->comp.x_int_wall + all->comp.x_tile_wall] != '0')
				return (VERT);
			all->comp.x_int_wall += all->comp.tile_step_x;
			all->comp.y_intercept += (all->comp.y_step * all->comp.tile_step_y);
		}
	}
	return (0);
}
