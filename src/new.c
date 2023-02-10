/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:22:29 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/10 19:45:27 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void draw_line(t_data *win_img_data, int x, int start_y, int end_y, int color)
{
	while (start_y < end_y)
	{
		my_mlx_pixel_put(win_img_data, x,  start_y, color);
		start_y++;
	}
}

int	check_hit_vert(t_all *all)
{
	if (all->player.ray.angle >= 0 && all->player.ray.angle <= 180)
	{
		while ((all->comp.y_intercept > (all->comp.y_int_wall * Field)))
		{
			if (all->map.map[(int)all->comp.y_intercept / Field] \
				[(int)all->comp.x_int_wall + all->comp.x_tile_wall] != '0')
				return (VERT);
			all->comp.x_int_wall += all->comp.tile_step_x;
			all->comp.y_intercept += (all->comp.y_step * all->comp.tile_step_y);
		}
	}
	else
	{
		while ((all->comp.y_intercept < (all->comp.y_int_wall * Field)))
		{
			if (all->map.map[(int)all->comp.y_intercept / Field] \
				[(int)all->comp.x_int_wall + all->comp.x_tile_wall] != '0')
				return (VERT);
			all->comp.x_int_wall += all->comp.tile_step_x;
			all->comp.y_intercept += (all->comp.y_step * all->comp.tile_step_y);
		}
	}
	return (0);
}

int	check_hit_horiz(t_all *all)
{
	if (all->player.ray.angle >= 90 && all->player.ray.angle <= 270)
	{
		while ((all->comp.x_intercept > all->comp.x_int_wall * Field))
		{
			if (all->map.map[(int)all->comp.y_int_wall + all->comp.y_tile_wall] \
				[(int)all->comp.x_intercept / Field] != '0')
				return (HORIZ);
			all->comp.y_int_wall += all->comp.tile_step_y;
			all->comp.x_intercept += (all->comp.x_step * all->comp.tile_step_x);
		}
	}
	else
	{
		while (all->comp.x_intercept < all->comp.x_int_wall * Field)
		{
			if (all->map.map[(int)all->comp.y_int_wall + all->comp.y_tile_wall] \
				[(int)all->comp.x_intercept / Field] != '0')
				return (HORIZ);
			all->comp.y_int_wall += all->comp.tile_step_y;
			all->comp.x_intercept += (all->comp.x_step * all->comp.tile_step_x);
		}
	}
	return (0);
}

static void	get_comp_1(t_all *all)
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
		all->comp.y_step = ft_fabs(tan(d_to_rdn(all->comp.ray_angle)) * Field);
		all->comp.x_step = ft_fabs(Field / tan(d_to_rdn(all->comp.ray_angle)));
		all->comp.x_intercept = all->player.x + ft_fabs(all->comp.dy / tan(d_to_rdn(all->comp.ray_angle))) * all->comp.tile_step_x;
		all->comp.y_intercept = all->player.y + ft_fabs(all->comp.dx * tan(d_to_rdn(all->comp.ray_angle))) * all->comp.tile_step_y;
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
