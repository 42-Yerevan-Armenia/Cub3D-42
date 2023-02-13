/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:26:08 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/13 13:47:45 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	event(int key, void *param)
{
	t_all	*all;
	double	new_x;
	double	new_y;

	all = param;
	if (key == KEY_W)
	{
		new_x = all->player.x + (cos(d_to_rdn(all->player.angle)) * Step_walk);
		new_y = all->player.y - (sin(d_to_rdn(all->player.angle)) * Step_walk);
		// printf("%d\n", Dis_wall * all->comp.tile_step_x);
		if (all->map.map[(int)((new_y + (Dis_wall * all->comp.tile_step_y)) / Field)][(int)((new_x + (Dis_wall * all->comp.tile_step_x)) / Field)] != '1')
		{
			all->player.x = new_x;
			all->player.y = new_y;
		}
	}
	else if (key == KEY_S)
	{
		new_x = all->player.x - (cos(d_to_rdn(all->player.angle)) * Step_walk);
		new_y = all->player.y + (sin(d_to_rdn(all->player.angle)) * Step_walk);
		if (all->map.map[(int)((new_y + (Dis_wall * all->comp.tile_step_y)) / Field)][(int)((new_x + (Dis_wall * all->comp.tile_step_y)) / Field)] != '1')
		{
			all->player.x = new_x;
			all->player.y = new_y;
		}
	}
	else if (key == KEY_A)
	{
		new_x = all->player.x + (cos(d_to_rdn(all->player.angle + 90)) * Step_walk);
		new_y = all->player.y - (sin(d_to_rdn(all->player.angle + 90)) * Step_walk);
		if (all->map.map[(int)((new_y + (Dis_wall * all->comp.tile_step_y)) / Field)][(int)((new_x + (Dis_wall * all->comp.tile_step_y)) / Field)] != '1')
		{
			all->player.x = new_x;
			all->player.y = new_y;
		}
	}
	else if (key == KEY_D)
	{
		new_x = all->player.x - (cos(d_to_rdn(all->player.angle + 90)) * Step_walk);
		new_y = all->player.y + (sin(d_to_rdn(all->player.angle + 90)) * Step_walk);
		if (all->map.map[(int)((new_y + (Dis_wall * all->comp.tile_step_y)) / Field)][(int)((new_x + (Dis_wall * all->comp.tile_step_y)) / Field)] != '1')
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
