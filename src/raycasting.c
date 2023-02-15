/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:42:08 by arakhurs          #+#    #+#             */
/*   Updated: 2023/02/15 11:57:45 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	get_intercept(t_all *all, t_ray *ray)
{
	all->comp.x_tile_wall = 0;
	all->comp.y_tile_wall = 0;
	if (ray->angle >= 90 && ray->angle <= 270)
	{
		all->comp.x_int_wall = ((int)all->player.x / Field);
		all->comp.x_tile_wall = -1;
	}
	else
		all->comp.x_int_wall = ((int)all->player.x / Field) + 1;
	if (ray->angle >= 0 && ray->angle <= 180)
	{
		all->comp.y_tile_wall = -1;
		all->comp.y_int_wall = ((int)all->player.y / Field);
	}
	else
		all->comp.y_int_wall = ((int)all->player.y / Field) + 1;
	get_componets(all, ray);
	while (1)
	{
		if (check_hit_vert(all) == VERT)
			return (VERT);
		if (check_hit_horiz(all) == HORIZ)
			return (HORIZ);
	}
	return (0);
}

static void	ray_cast_init(t_all *all, int ray_count)
{
	ray_count = 0;
	all->player.ray.angle = all->player.angle;
	increament_in_range(360, all->half_fov, &all->player.ray.angle);
	if (all->win_img_data.img != NULL)
		mlx_destroy_image(all->mlx, all->win_img_data.img);
	all->win_img_data.img = mlx_new_image(all->mlx, Win_x, Win_y);
	all->win_img_data.addr = mlx_get_data_addr(all->win_img_data.img, \
		&all->win_img_data.bits_per_pixel, &all->win_img_data.line_length, \
			&all->win_img_data.endian);
}

static void	ray_cast_in_loop(t_all *all, int ray_count)
{
	adjust_dx_dy(&all->comp, all->player.ray.angle, all->player.x, \
		all->player.y);
	adjust_tile_step(&all->comp, all->player.ray.angle);
	all->player.ray.dis = ray_distance(all, &all->player.ray, 1);
	all->comp.height_wall = ((float)(Win_y * Field) / 2) / \
	all->player.ray.dis;
	if (all->comp.height_wall >= Win_y || (int)all->player.ray.dis == 0)
		all->comp.height_wall = Win_y;
	all->comp.half_h_wall = all->comp.height_wall / 2;
	draw_line(all, ray_count, 0, all->half_win_y - all->comp.half_h_wall);
}

void	ray_casting(t_all *all, int ray_count)
{
	int	y_win;

	ray_cast_init(all, ray_count);
	while (ray_count < Win_x)
	{
		ray_cast_in_loop(all, ray_count);
		y_win = all->half_win_y - all->comp.half_h_wall;
		while (y_win < all->half_win_y + all->comp.half_h_wall)
		{
			if (all->comp.pic_y >= 1920)
				all->comp.pic_y = 1919;
			my_mlx_pixel_put(&all->win_img_data, ray_count, y_win, \
				get_color(&all->imgs_wall[all->comp.wall_index].data, \
					all->comp.pic_x, all->comp.pic_y));
			y_win++;
			all->comp.pic_y += all->comp.pic_y_step;
		}
		draw_line(all, ray_count, all->half_win_y + \
			all->comp.half_h_wall, Win_y);
		ray_count += 1;
		decreament_in_range(360, ((double)Fov / (double)Win_x), \
			&all->player.ray.angle);
	}
	draw_minimap(all);
	mlx_put_image_to_window(all->mlx, all->win, all->win_img_data.img, 0, 0);
}
