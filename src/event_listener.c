/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:26:08 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/05 17:33:01 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	event(int key, void *param)
{
	t_all 	*all;
	double		new_x;
	double		new_y;

	all = param;
	if (key == KEY_W)
	{
		new_x = all->player.x + (cos(degree_to_radians(all->player.angle)) * Step_walk);
		new_y = all->player.y - (sin(degree_to_radians(all->player.angle)) * Step_walk);
		// printf("%d\n", Dis_wall * all->comp.tile_step_x);
		if (all->map.map[(int)((new_y + (Dis_wall * all->comp.tile_step_y)) / Field)][(int)((new_x + (Dis_wall * all->comp.tile_step_x)) / Field)] != '1')
		{
			all->player.x = new_x;
			all->player.y = new_y;
		}
	}
	else if (key == KEY_S)
	{
		new_x = all->player.x - (cos(degree_to_radians(all->player.angle)) * Step_walk);
		new_y = all->player.y + (sin(degree_to_radians(all->player.angle)) * Step_walk);
		if (all->map.map[(int)((new_y + (Dis_wall * all->comp.tile_step_y)) / Field)][(int)((new_x + (Dis_wall * all->comp.tile_step_y)) / Field)] != '1')
		{
			all->player.x = new_x;
			all->player.y = new_y;
		}
	}
	else if (key == KEY_A)
	{
		new_x = all->player.x + (cos(degree_to_radians(all->player.angle + 90)) * Step_walk);
		new_y = all->player.y - (sin(degree_to_radians(all->player.angle + 90)) * Step_walk);
		if (all->map.map[(int)((new_y + (Dis_wall * all->comp.tile_step_y)) / Field)][(int)((new_x + (Dis_wall * all->comp.tile_step_y)) / Field)] != '1')
		{
			all->player.x = new_x;
			all->player.y = new_y;
		}
	}
	else if (key == KEY_D)
	{
		new_x = all->player.x - (cos(degree_to_radians(all->player.angle + 90)) * Step_walk);
		new_y = all->player.y + (sin(degree_to_radians(all->player.angle + 90)) * Step_walk);
		if (all->map.map[(int)((new_y + (Dis_wall * all->comp.tile_step_y)) / Field)][(int)((new_x + (Dis_wall * all->comp.tile_step_y)) / Field)] != '1')
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
