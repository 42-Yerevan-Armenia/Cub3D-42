/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:26:08 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/15 19:14:16 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static double	get_min(double *dist_w)
{
	double	res;
	int		i;

	res = dist_w[0];
	i = -1;
	while (++i < 3)
		if (dist_w[i] < res)
			res = dist_w[i];
	return (res);
}

static double	dist_walls(t_all *all, double *dist_w, double s_a)
{
	double	tmp;

	tmp = all->player.ray.angle;
	all->player.ray.angle = all->player.angle;
	increament_in_range(360, s_a, &all->player.ray.angle);
	decreament_in_range(360, 45, &all->player.ray.angle);
	adjust_params(all);
	dist_w[0] = ray_distance(all, 2);
	increament_in_range(360, 45, &all->player.ray.angle);
	adjust_params(all);
	dist_w[1] = ray_distance(all, 2);
	increament_in_range(360, 45, &all->player.ray.angle);
	adjust_params(all);
	dist_w[2] = ray_distance(all, 2);
	all->player.ray.angle = tmp;
	return (get_min(dist_w));
}

static void	get_new_x_y(t_all *all, double angle, int mode, double start_angle)
{
	double	new_x;
	double	new_y;
	double	dist_from_wall;

	dist_from_wall = dist_walls(all, all->comp.dist_walls, start_angle);
	if (mode == 1)
	{
		new_x = all->player.x + (cos(d_to_rdn(angle)) * Step_walk);
		new_y = all->player.y - (sin(d_to_rdn(angle)) * Step_walk);
	}
	else
	{
		new_x = all->player.x - (cos(d_to_rdn(angle)) * Step_walk);
		new_y = all->player.y + (sin(d_to_rdn(angle)) * Step_walk);
	}
	if (get_dist_points(new_x, new_y, all->player.x, all->player.y)
		< dist_from_wall - Dis_wall)
	{
		all->player.x = new_x;
		all->player.y = new_y;
	}
}

int	event(int key, void *param)
{
	t_all	*all;

	all = param;
	if (valid_key(key) == 0)
		return (1);
	if (key == KEY_W)
		get_new_x_y(all, all->player.angle, 1, 0);
	else if (key == KEY_S)
		get_new_x_y(all, all->player.angle, 2, 180);
	else if (key == KEY_A)
		get_new_x_y(all, all->player.angle + 90, 1, 90);
	else if (key == KEY_D)
		get_new_x_y(all, all->player.angle + 90, 2, 270);
	else if (key == KEY_ARROW_LEFT)
		increament_in_range(360, Step_angle, &all->player.angle);
	else if (key == KEY_ARROW_RIGHT)
		decreament_in_range(360, Step_angle, &all->player.angle);
	else if (key == KEY_ESC)
		ft_destroy(all);
	ray_casting(all);
	draw_minimap(all);
	return (0);
}
