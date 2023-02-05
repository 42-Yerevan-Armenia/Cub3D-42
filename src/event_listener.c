/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:26:08 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/02 18:07:01 by vaghazar         ###   ########.fr       */
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
		// printf("all->player.angle = %f\n", all->player.angle);
		if (all->map.map[(int)(new_y / Field)][(int)(new_x / Field)] != '1')
		{
			all->player.x = new_x;
			all->player.y = new_y;
		}
	}
	else if (key == KEY_S)
	{
		new_x = all->player.x - (cos(degree_to_radians(all->player.angle)) * Step_walk);
		new_y = all->player.y + (sin(degree_to_radians(all->player.angle)) * Step_walk);
		// printf("all->player.angle = %f\n", all->player.angle);
		if (all->map.map[(int)(new_y / Field)][(int)(new_x / Field)] != '1')
		{
			all->player.x = new_x;
			all->player.y = new_y;
		}
	}
	else if (key == KEY_A)
	{
		new_x = all->player.x + (cos(degree_to_radians(all->player.angle + 90)) * Step_walk);
		new_y = all->player.y - (sin(degree_to_radians(all->player.angle + 90)) * Step_walk);
		// printf("x = %f\n", new_x);
		// printf("y = %f\n", new_y);
		// printf("%f\n", all->player.angle + 90);
		// printf("sin(degree_to_radians(all->player.angle + 90)) = %f\n", sin(degree_to_radians(all->player.angle + 90)));
		// printf("%f\n", (sin(degree_to_radians(all->player.angle + 90)) * Step_walk));
		if (all->map.map[(int)(new_y / Field)][(int)(new_x / Field)] != '1')
		{
			all->player.x = new_x;
			all->player.y = new_y;
		}
		// printf("KEY_AKEY_AKEY_AKEY_AKEY_AKEY_AKEY_AKEY_AKEY_AKEY_AKEY_AKEY_AKEY_AKEY_AKEY_AKEY_A\n");
		// printf("x = %f\n", all->player.x);
		// printf("y = %f\n", all->player.y);
		// printf("all->player.angle = %f\n", all->player.angle);
		// printf("KEY_AKEY_AKEY_AKEY_AKEY_AKEY_AKEY_AKEY_AKEY_AKEY_AKEY_AKEY_AKEY_AKEY_AKEY_AKEY_A\n");
	}
	else if (key == KEY_D)
	{
		new_x = all->player.x - (cos(degree_to_radians(all->player.angle + 90)) * Step_walk);
		new_y = all->player.y + (sin(degree_to_radians(all->player.angle + 90)) * Step_walk);
		// printf("sin(degree_to_radians(all->player.angle + 90)) = %f\n", sin(degree_to_radians(all->player.angle + 90)));
		// printf("x = %f\n", new_x);
		// printf("y = %f\n", new_y);
		// printf("%f\n", all->player.angle + 90);
		if (all->map.map[(int)(new_y / Field)][(int)(new_x / Field)] != '1')
		{
			all->player.x = new_x;
			all->player.y = new_y;
		}
		// printf("KEY_DKEY_DKEY_DKEY_DKEY_DKEY_DKEY_DKEY_DKEY_DKEY_DKEY_DKEY_DKEY_DKEY_DKEY_DKEY_DKEY_DKEY_D\n");
		// printf("x = %f\n", all->player.x);
		// printf("y = %f\n", all->player.y);
		// printf("all->player.angle = %f\n", all->player.angle);
		// printf("KEY_DKEY_DKEY_DKEY_DKEY_DKEY_DKEY_DKEY_DKEY_DKEY_DKEY_DKEY_DKEY_DKEY_DKEY_DKEY_DKEY_DKEY_D\n");
	}
	else if (key == KEY_Q)
		increament_in_range(360, Step_angle, &all->player.angle);
	else if (key == KEY_E)
		decreament_in_range(360, Step_angle, &all->player.angle);
	else if (key == KEY_ESC)
		exit(1);
	// if (all->player.x >= 199)
	// {
	// 	printf("barev\n");
	// 	pause();
	// 	// printf("all->comp.height_wall = %d\n", all->comp.height_wall);
	// }
	// printf("x = %lf\n", all->player.x);
	// printf("y = %lf\n", all->player.y);
	ray_casting(all);
	// printf("barev\n");
	return (0);
}

void event_listener(t_all *all)
{
	mlx_hook(all->win, 2, 0, &event, all);
}
