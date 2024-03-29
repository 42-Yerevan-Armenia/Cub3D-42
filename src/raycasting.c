/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:42:08 by arakhurs          #+#    #+#             */
/*   Updated: 2023/02/15 21:16:06 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	adjust_params(t_all *all)
{
	adjust_dx_dy(&all->comp, all->player.ray.angle,
		all->player.x, all->player.y);
	adjust_tile_step(&all->comp, all->player.ray.angle);
}

void	new_win_img(t_all *all)
{
	if (all->win_img_data.img != NULL)
		mlx_destroy_image(all->mlx, all->win_img_data.img);
	all->win_img_data.img = mlx_new_image(all->mlx, Win_x, Win_y);
	all->win_img_data.addr = mlx_get_data_addr(all->win_img_data.img,
			&all->win_img_data.bits_per_pixel, &all->win_img_data.line_length,
			&all->win_img_data.endian);
}

void	ray_casting(t_all *all)
{
	int	ray_count;

	ray_count = 0;
	all->player.ray.angle = all->player.angle;
	increament_in_range(360, all->half_fov, &all->player.ray.angle);
	new_win_img(all);
	while (ray_count < Win_x)
	{
		adjust_params(all);
		all->player.ray.dis = ray_distance(all, 1);
		all->comp.height_wall = ((float)(Win_y * Field) / 2)
			/ all->player.ray.dis;
		if (all->comp.height_wall >= Win_y
			|| (int)all->player.ray.dis == 0)
			all->comp.height_wall = Win_y;
		all->comp.half_h_wall = all->comp.height_wall / 2;
		draw_img(all, ray_count);
		ray_count += 1;
		decreament_in_range(360, (Fov / (double)Win_x), &all->player.ray.angle);
	}
	mlx_put_image_to_window(all->mlx, all->win, all->win_img_data.img, 0, 0);
}
