/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raydistance.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:57:34 by arakhurs          #+#    #+#             */
/*   Updated: 2023/02/15 21:03:16 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static void	ray_distance_horiz(t_all *all, double *current_distance, \
	double *correct_distance)
{
	*current_distance = get_dist_points(all->player.x, all->player.y,
			all->comp.x_intercept, (all->comp.y_int_wall * Field));
	*correct_distance = *current_distance
		* cos(d_to_rdn(all->player.ray.angle - all->player.angle));
	all->comp.height_wall = (((double)((double)Win_y * (double)Field)
				/ (double)2) / *correct_distance);
	if (all->player.ray.angle >= 0 && all->player.ray.angle <= 180)
	{
		field_len(all->comp.x_intercept, &all->comp, all->imgs_wall[0].height);
		all->comp.wall_index = 1;
	}
	else
	{
		field_len(all->comp.x_intercept, &all->comp, all->imgs_wall[0].height);
		all->comp.wall_index = 3;
	}
}

static void	ray_distance_vert(t_all *all, double *current_distance, \
	double *correct_distance)
{
	*current_distance = get_dist_points(all->player.x, all->player.y,
			all->comp.x_int_wall * Field, all->comp.y_intercept);
	*correct_distance = *current_distance
		* cos(d_to_rdn(all->player.ray.angle - all->player.angle));
	all->comp.height_wall = (((double)((double)Win_y * (double)Field)
				/ (double)2) / *correct_distance);
	if (all->player.ray.angle >= 90 && all->player.ray.angle <= 270)
	{
		field_len(all->comp.y_intercept, &all->comp, all->imgs_wall[0].height);
		all->comp.wall_index = 0;
	}
	else
	{
		field_len(all->comp.y_intercept, &all->comp, all->imgs_wall[0].height);
		all->comp.wall_index = 2;
	}
}

void	get_intercept_1(t_all *all, double ray_angle)
{
	if (ray_angle >= 90 && ray_angle <= 270)
	{
		all->comp.x_int_wall = ((int)all->player.x / Field);
		all->comp.x_tile_wall = -1;
	}
	else
		all->comp.x_int_wall = ((int)all->player.x / Field) + 1;
	if (ray_angle >= 0 && ray_angle <= 180)
	{
		all->comp.y_tile_wall = -1;
		all->comp.y_int_wall = ((int)all->player.y / Field);
	}
	else
		all->comp.y_int_wall = ((int)all->player.y / Field) + 1;
}

static int	get_intercept(t_all *all)
{
	int		a;
	double	ray_angle;

	a = 5;
	ray_angle = all->player.ray.angle;
	all->comp.x_tile_wall = 0;
	all->comp.y_tile_wall = 0;
	all->player.ray.x = (int)all->player.x;
	all->player.ray.y = (int)all->player.y;
	get_intercept_1(all, ray_angle);
	get_componets(all, &all->player.ray);
	while (1)
	{
		if (check_hit_vert(all) == VERT)
			return (VERT);
		if (check_hit_horiz(all) == HORIZ)
			return (HORIZ);
	}
	return (0);
}

double	ray_distance(t_all *all, int mode)
{
	double	current_distance;
	double	correct_distance;

	if (get_intercept(all) == HORIZ)
	{
		ray_distance_horiz(all, &current_distance, &correct_distance);
	}
	else
		ray_distance_vert(all, &current_distance, &correct_distance);
	if (mode == 1)
		return (correct_distance);
	else
		return (current_distance);
}
