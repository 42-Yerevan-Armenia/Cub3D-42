/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:26:08 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/06 17:12:35 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	event(int key, void *param)
{
	t_all 	*all;
	double		new_x;
	double		new_y;

	all = param;
	// printf("all->player.x = %lf\n", all->player.x);
	// printf("all->player.y = %lf\n", all->player.y);
	// printf("all->player.angle = %lf\n", all->player.angle);
	if (all->player.angle >= 90 && all->player.angle <= 270)
		all->comp.step_w = -1;
	else
		all->comp.step_w = 1;
	if (all->player.angle >= 0 && all->player.angle <= 180)
		all->comp.step_d = -1;
	else
		all->comp.step_d = 1;
	if (key == KEY_W)
	{
		// all->comp.step_d = ;
		new_x = all->player.x + (cos(degree_to_radians(all->player.angle)) * Step_walk);
		new_y = all->player.y - (sin(degree_to_radians(all->player.angle)) * Step_walk);
		if (all->map.map[(int)((new_y - Dis_wall) / Field)][(int)((new_x + Dis_wall) / Field)] != '1')
		{
			all->player.x = new_x;
			all->player.y = new_y;
		}
	}
	else if (key == KEY_S)
	{
		new_x = all->player.x - (cos(degree_to_radians(all->player.angle)) * Step_walk);
		new_y = all->player.y + (sin(degree_to_radians(all->player.angle)) * Step_walk);
		if (all->map.map[(int)((new_y + Dis_wall) / Field)][(int)((new_x - Dis_wall) / Field)] != '1')
		{
			all->player.x = new_x;
			all->player.y = new_y;
		}
	}
	else if (key == KEY_A)
	{
		new_x = all->player.x + (cos(degree_to_radians(all->player.angle + 90)) * Step_walk);
		new_y = all->player.y - (sin(degree_to_radians(all->player.angle + 90)) * Step_walk);
		// printf("new_y = %lf\n", new_y);
		// printf("new_x = %lf\n", new_x);
		// printf("%lf\n", new_y + (Dis_wall));
		// printf("%lf\n", new_x + (Dis_wall));
		// printf("new_y = %d\n", (int)((new_y - Dis_wall) / Field));
		// printf("new_x = %d\n", (int)((new_x + Dis_wall) / Field));
		if (all->map.map[(int)((new_y - Dis_wall) / Field)][(int)((new_x + Dis_wall) / Field)] != '1')
		{
			all->player.x = new_x;
			all->player.y = new_y;
		}
	}
	else if (key == KEY_D)
	{
		new_x = all->player.x - (cos(degree_to_radians(all->player.angle + 90)) * Step_walk);
		new_y = all->player.y + (sin(degree_to_radians(all->player.angle + 90)) * Step_walk);
		if (all->map.map[(int)((new_y + (Dis_wall)) / Field)][(int)((new_x - (Dis_wall)) / Field)] != '1')
		{
			all->player.x = new_x;
			all->player.y = new_y;
		}
	}
	else if (key == KEY_Q)
		increament_in_range(360, Step_angle, &all->player.angle);
	else if (key == KEY_E)
		decreament_in_range(360, Step_angle, &all->player.angle);
	else if (key == KEY_ESC)
		exit(1);
	// if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
	// 	adjust_dx_dy(&all->comp, all->player.angle, all->player.x, all->player.y);
	// else if (key == KEY_Q || key == KEY_E)
	// 	adjust_tile_step(&all->comp, all->player.angle);
	ray_casting(all);
	return (0);
}

void event_listener(t_all *all)
{
	mlx_hook(all->win, 2, 0, &event, all);
}
