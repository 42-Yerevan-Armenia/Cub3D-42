/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   components.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:11:08 by arakhurs          #+#    #+#             */
/*   Updated: 2023/02/15 20:21:45 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static void	get_comp_2(t_all *all, t_ray *ray)
{
	all->comp.y_step = ft_fabs(tan(d_to_rdn(all->comp.ray_angle)) * Field);
	all->comp.x_step = ft_fabs(Field / tan(d_to_rdn(all->comp.ray_angle)));
	all->comp.x_intercept = all->player.x + ft_fabs(all->comp.dy
			/ tan(d_to_rdn(all->comp.ray_angle))) * all->comp.tile_step_x;
	all->comp.y_intercept = all->player.y + ft_fabs(all->comp.dx
			* tan(d_to_rdn(all->comp.ray_angle))) * all->comp.tile_step_y;
}

static void	get_comp_1(t_all *all, t_ray *ray)
{
	if (ray->angle == 0
		|| ray->angle == 360
		|| ray->angle == 180)
	{
		all->comp.y_step = 0;
		all->comp.x_step = Field;
		all->comp.y_intercept = all->player.y;
		all->comp.x_intercept = all->player.x
			+ (all->comp.dx * all->comp.tile_step_x);
	}
	else if (ray->angle == 90
		|| ray->angle == 270)
	{
		all->comp.y_step = Field;
		all->comp.x_step = 0;
		all->comp.x_intercept = all->player.x;
		all->comp.y_intercept = all->player.y
			+ (all->comp.dy * all->comp.tile_step_y);
	}
	else
		get_comp_2(all, ray);
}

void	get_componets(t_all *all, t_ray *ray)
{
	all->comp.ray_angle = ray->angle;
	if (ray->angle >= 90 && ray->angle <= 180)
		all->comp.ray_angle = ft_fabs(180 - ray->angle);
	else if (ray->angle >= 180 && ray->angle <= 270)
		all->comp.ray_angle = ft_fabs(ray->angle - 180);
	else if (ray->angle >= 270 && ray->angle <= 360)
		all->comp.ray_angle = ft_fabs(360 - ray->angle);
	get_comp_1(all, ray);
}
