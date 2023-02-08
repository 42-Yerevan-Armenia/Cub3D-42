/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_componets.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:33:04 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/07 16:11:22 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void get_comp_1(t_all *all)
{
	if (all->player.ray.angle == 0
		|| all->player.ray.angle == 360
		|| all->player.ray.angle == 180)
	{
		all->comp.y_step = 0;
		all->comp.x_step = Field;
		all->comp.y_intercept = all->player.y;
		all->comp.x_intercept = all->player.x + (all->comp.dx * all->comp.tile_step_x);
	}
	else if (all->player.ray.angle == 90
		|| all->player.ray.angle == 270)
	{
		all->comp.y_step = Field;
		all->comp.x_step = 0;
		all->comp.x_intercept = all->player.x;
		all->comp.y_intercept = all->player.y + (all->comp.dy * all->comp.tile_step_y);
	}
	else
	{
		all->comp.y_step = ft_fabs(tan(degree_to_radians(all->comp.ray_angle)) * Field);
		all->comp.x_step = ft_fabs(Field / tan(degree_to_radians(all->comp.ray_angle)));
		all->comp.x_intercept = all->player.x + ft_fabs(all->comp.dy / tan(degree_to_radians(all->comp.ray_angle))) * all->comp.tile_step_x;
		all->comp.y_intercept = all->player.y + ft_fabs(all->comp.dx * tan(degree_to_radians(all->comp.ray_angle))) * all->comp.tile_step_y;
	}
}

void	get_componets(t_all *all)
{
	all->comp.ray_angle = all->player.ray.angle;
	if (all->player.ray.angle >= 90 && all->player.ray.angle <= 180)
		all->comp.ray_angle = ft_fabs(180 - all->player.ray.angle);
	else if (all->player.ray.angle >= 180 && all->player.ray.angle <= 270)
		all->comp.ray_angle = ft_fabs(all->player.ray.angle - 180);
	else if (all->player.ray.angle >= 270 && all->player.ray.angle <= 360)
		all->comp.ray_angle = ft_fabs(360 - all->player.ray.angle);
	get_comp_1(all);
}

