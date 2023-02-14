/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:26:08 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/14 16:58:03 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	adjust_move_dir(int	*x_move_dir, int *y_move_dir, double angle, double step)
{
	double	tmp;

	tmp = angle;

	increament_in_range(360, step, &tmp);
	if (tmp > 90 && tmp < 270)
		*x_move_dir = -1;
	else if (tmp != 90 && tmp != 270)
		*x_move_dir = 1;
	else
		*x_move_dir = 0;
	if (tmp >= 0 && tmp <= 180)
		*y_move_dir = -1;
	else if (tmp != 0 && tmp != 180)
		*y_move_dir = 1;
	else
		*y_move_dir = 0;
}

double	dist_walls(t_all *all, double *dist_walls, double p_angle)
{
	double	tmp;

	tmp = all->player.ray.angle;
	decreament_in_range(360, 45, &all->player.ray.angle);
	dist_walls[0] = ray_distance(all, 2);
	increament_in_range(360, 45, &all->player.ray.angle);
	adjust_tile_step(&all->comp, all->player.ray.angle);
	adjust_dx_dy(&all->comp, all->player.ray.angle, all->player.x, all->player.y);
	dist_walls[1] = ray_distance(all, 2);
	increament_in_range(360, 45, &all->player.ray.angle);
	adjust_dx_dy(&all->comp, all->player.ray.angle, all->player.x, all->player.y);
	adjust_tile_step(&all->comp, all->player.ray.angle);
	dist_walls[2] = ray_distance(all, 2);
	int  i = 0;
	// while (i < 5)
	// 	printf("dist_walls = %lf\n", dist_walls[i++]);
	all->player.ray.angle = tmp;
	// adjust_tile_step(&all->comp, all->player.ray.angle);
	// adjust_dx_dy(&all->comp, all->player.ray.angle, all->player.x, all->player.y);
	tmp = dist_walls[0];
	i = -1;
	while (++i < 3)
		if (dist_walls[i] < tmp)
			tmp = dist_walls[i];
	return (tmp);

}

double	get_dist_points(double p1_x, double p1_y, double p2_x, double p2_y)
{
	return (sqrt(pow(ft_fabs(p1_x - p2_x), 2) + pow(ft_fabs(p1_y - p2_y), 2)));
}

int	event(int key, void *param)
{
	t_all	*all;
	double	new_x;
	double	new_y;
	double	wall_distance;
	all = param;
	double	move_dir = all->player.angle;
	double	dist_from_wall;
	dist_from_wall = dist_walls(all, all->comp.dist_walls, all->player.angle);
	// printf("wall_distance = %lf\n", wall_distance);
	if (key == KEY_W)
	{
		// all->player.ray.angle = all->player.angle;
		// wall_distance = ray_distance(all);
		// adjust_move_dir(&all->comp.x_move_dir, &all->comp.y_move_dir, all->player.angle, 0);
		new_x = all->player.x + (cos(d_to_rdn(all->player.angle)) * Step_walk);
		new_y = all->player.y - (sin(d_to_rdn(all->player.angle)) * Step_walk);
		// printf("%d\n", Dis_wall * all->comp.tile_step_x);
		// if (all->map.map[(int)((new_y + (Dis_wall * all->comp.y_move_dir)) / Field)][(int)((new_x + (Dis_wall * all->comp.x_move_dir)) / Field)] != '1')
		if (get_dist_points(new_x, new_y, all->player.x, all->player.y) <= dist_from_wall - Dis_wall)
		{
			all->player.x = new_x;
			all->player.y = new_y;
		}
	}
	else if (key == KEY_S)
	{
		// all->player.ray.angle = all->player.angle;
		// increament_in_range(360, 180, &all->player.ray.angle);
		// wall_distance = ray_distance(all);
		// increament_in_range(360, 180, )
		// adjust_move_dir(&all->comp.x_move_dir, &all->comp.y_move_dir, all->player.angle + 180);
		// adjust_move_dir(&all->comp.x_move_dir, &all->comp.y_move_dir, all->player.angle, 0);
		new_x = all->player.x - (cos(d_to_rdn(all->player.angle)) * Step_walk);
		new_y = all->player.y + (sin(d_to_rdn(all->player.angle)) * Step_walk);
		// if (all->map.map[(int)((new_y + (Dis_wall * all->comp.tile_step_y)) / Field)][(int)((new_x + (Dis_wall * all->comp.tile_step_y)) / Field)] != '1')
		if (get_dist_points(new_x, new_y, all->player.x, all->player.y) <= dist_from_wall - Dis_wall)
		{
			all->player.x = new_x;
			all->player.y = new_y;
		}
	}
	else if (key == KEY_A)
	{
		// all->player.ray.angle = all->player.angle;
		// increament_in_range(360, 90, &all->player.ray.angle);
		// wall_distance = ray_distance(all);
		// adjust_move_dir(&all->comp.x_move_dir, &all->comp.y_move_dir, all->player.angle, 90);
		new_x = all->player.x + (cos(d_to_rdn(all->player.angle + 90)) * Step_walk);
		new_y = all->player.y - (sin(d_to_rdn(all->player.angle + 90)) * Step_walk);
		// if (all->map.map[(int)((new_y + (Dis_wall * all->comp.tile_step_y)) / Field)][(int)((new_x + (Dis_wall * all->comp.tile_step_y)) / Field)] != '1')
		if (get_dist_points(new_x, new_y, all->player.x, all->player.y) <= dist_from_wall - Dis_wall)
		{
			all->player.x = new_x;
			all->player.y = new_y;
		}
	}
	else if (key == KEY_D)
	{
		new_x = all->player.x - (cos(d_to_rdn(all->player.angle + 90)) * Step_walk);
		new_y = all->player.y + (sin(d_to_rdn(all->player.angle + 90)) * Step_walk);
		// if (all->map.map[(int)((new_y + (Dis_wall * all->comp.tile_step_y)) / Field)][(int)((new_x + (Dis_wall * all->comp.tile_step_y)) / Field)] != '1')
		if (get_dist_points(new_x, new_y, all->player.x, all->player.y) <= dist_from_wall - Dis_wall)
		{
			all->player.x = new_x;
			all->player.y = new_y;
		}
	}
	else if (key == KEY_ARROW_LEFT)
		increament_in_range(360, Step_angle, &all->player.angle);
	else if (key == KEY_ARROW_RIGHT)
		decreament_in_range(360, Step_angle, &all->player.angle);
	else if (key == KEY_ESC)
		ft_destroy(all);
	// if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
	// 	adjust_dx_dy(&all->comp, all->player.angle, all->player.x, all->player.y);
	// else if (key == KEY_Q || key == KEY_E)
	// 	adjust_tile_step(&all->comp, all->player.angle);
	ray_casting(all);
	draw_minimap(all);
	draw_minimaps(all->mlx, all->win, all->player, all);
	return (0);
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
