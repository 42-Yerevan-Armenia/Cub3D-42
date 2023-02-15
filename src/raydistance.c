/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raydistance.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:57:34 by arakhurs          #+#    #+#             */
/*   Updated: 2023/02/15 11:06:56 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static void	r_d_1(t_all *all, t_ray *ray)
{
	if (ray->angle >= 0 && ray->angle <= 180)
	{
		field_len(all->comp.x_intercept, &all->comp, \
			all->imgs_wall[0].height, START_LEFT);
		all->comp.wall_index = 1;
	}
	else
	{
		field_len(all->comp.x_intercept, &all->comp, \
			all->imgs_wall[0].height, START_RIGHT);
		all->comp.wall_index = 3;
	}	
}

static void	r_d_2(t_all *all, t_ray *ray)
{
	if (ray->angle >= 90 && ray->angle <= 270)
	{
		field_len(all->comp.y_intercept, &all->comp, \
			all->imgs_wall[0].height, START_LEFT);
		all->comp.wall_index = 0;
	}
	else
	{
		field_len(all->comp.y_intercept, &all->comp, \
			all->imgs_wall[0].height, START_RIGHT);
		all->comp.wall_index = 2;
	}	
}

double	ray_distance(t_all *all, t_ray *ray, int mode)
{
	if (get_intercept(all, ray) == HORIZ)
	{
		ray->cur_dis = sqrt(pow(ft_fabs(all->player.x - \
			all->comp.x_intercept), 2) + pow(ft_fabs(all->player.y - \
				(all->comp.y_int_wall * Field)), 2));
		ray->cor_dis = ray->cur_dis * cos(d_to_rdn(ray->angle - \
			all->player.angle));
		all->comp.height_wall = (((double)((double)Win_y * \
			(double)Field) / (double)2) / ray->cor_dis);
		r_d_1(all, ray);
	}
	else if (get_intercept(all, ray) != HORIZ)
	{
		ray->cur_dis = sqrt(pow(ft_fabs(all->player.x - all->comp.x_int_wall * \
		Field), 2) + pow(ft_fabs(all->player.y - all->comp.y_intercept), 2));
		ray->cor_dis = ray->cur_dis * cos(d_to_rdn(ray->angle - \
		all->player.angle));
		all->comp.height_wall = (((double)((double)Win_y * \
			(double)Field) / (double)2) / ray->cor_dis);
		r_d_2(all, ray);
	}
	if (mode == 1)
		return (ray->cor_dis);
	else
		return (ray->cur_dis);
}

double	get_height_wall(t_all *all, double num1, double num2)
{
	double	cur_dis;
	double	cor_dis;

	cur_dis = sqrt(pow(ft_fabs(all->player.x - all->comp.x_intercept), 2) + \
		pow(ft_fabs(all->player.y - (all->comp.y_int_wall * Field)), 2));
	cor_dis = cur_dis * cos(d_to_rdn(all->player.ray.angle - \
		all->player.angle));
	return ((((double)((double)Win_y * (double)Field) / (double)2) / cor_dis));
}
