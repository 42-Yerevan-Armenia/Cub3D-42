/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:42:08 by arakhurs          #+#    #+#             */
/*   Updated: 2023/02/10 19:45:27 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

double	get_height_wall(t_all *all, double num1, double num2)
{
	double	current_distance;
	double	correct_distance;

	current_distance = sqrt(pow(ft_fabs(all->player.x - all->comp.x_intercept), 2)
	+ pow(ft_fabs(all->player.y - (all->comp.y_int_wall * Field)), 2));
	correct_distance = current_distance * cos(d_to_rdn(all->player.ray.angle - all->player.angle));
	return ((((double)((double)Win_y * (double)Field) / (double)2) / correct_distance));
}

double	ray_distance(t_all *all)
{
	double	tmp;
	double current_distance;
	double correct_distance;
	if (get_intercept(all) == HORIZ)
	{
		current_distance = sqrt(pow(ft_fabs(all->player.x - all->comp.x_intercept), 2)
		+ pow(ft_fabs(all->player.y - (all->comp.y_int_wall * Field)), 2));
		correct_distance = current_distance * cos(d_to_rdn(all->player.ray.angle - all->player.angle));
		all->comp.height_wall = (((double)((double)Win_y * (double)Field) / (double)2) / correct_distance);
		if (all->player.ray.angle >= 0 && all->player.ray.angle <= 180)
		{
			field_len(all->comp.x_intercept, &all->comp, all->imgs_wall[0].height, START_LEFT);
			all->comp.wall_index = 1;
		}
		else
		{
			field_len(all->comp.x_intercept, &all->comp, all->imgs_wall[0].height, START_RIGHT);
			all->comp.wall_index = 3;
		}
	}
	else
	{
		current_distance = sqrt(pow(ft_fabs(all->player.x - all->comp.x_int_wall * Field), 2)
		+ pow(ft_fabs(all->player.y - all->comp.y_intercept), 2));
		correct_distance = current_distance * cos(d_to_rdn(all->player.ray.angle - all->player.angle));
		all->comp.height_wall = (((double)((double)Win_y * (double)Field) / (double)2) / correct_distance);
		if (all->player.ray.angle >= 90 && all->player.ray.angle <= 270)
		{
			field_len(all->comp.y_intercept, &all->comp, all->imgs_wall[0].height, START_LEFT);
			all->comp.wall_index = 0;
		}
		else
		{
			field_len(all->comp.y_intercept, &all->comp, all->imgs_wall[0].height, START_RIGHT);
			all->comp.wall_index = 2;
		}
	}
	return (correct_distance);
}

int	get_intercept(t_all *all)
{
	int		a;
	double	ray_angle;

	a = 5;
	ray_angle = all->player.ray.angle;
	all->comp.x_tile_wall = 0;
	all->comp.y_tile_wall = 0;
	all->player.ray.x = (int)all->player.x;
	all->player.ray.y = (int)all->player.y;
	if (ray_angle >= 90 && ray_angle <= 270)
	{
		all->comp.x_int_wall = ((int)all->player.x / Field);
		all->comp.x_tile_wall = -1;
	}
	else
		all->comp.x_int_wall = ((int)all->player.x / Field) + 1;
	if (ray_angle >= 0 && ray_angle <= 180)
	{
		all->comp.y_tile_wall = -1;
		all->comp.y_int_wall = ((int)all->player.y / Field);
	}
	else
		all->comp.y_int_wall = ((int)all->player.y / Field) + 1;
	get_componets(all);
	while (1)
	{
		if (check_hit_vert(all) == VERT)
			return (VERT);
		if (check_hit_horiz(all) == HORIZ)
			return (HORIZ);
	}
	return (0);
}

void ray_casting(t_all *all)
{
	int	y_win;
	int	ray_count;

	ray_count = 0;
	all->player.ray.angle = all->player.angle;
	increament_in_range(360, all->half_fov, &all->player.ray.angle);
	if (all->win_img_data.img != NULL)
		mlx_destroy_image(all->mlx, all->win_img_data.img);
	all->win_img_data.img =  mlx_new_image(all->mlx, Win_x, Win_y);
	all->win_img_data.addr = mlx_get_data_addr(all->win_img_data.img, &all->win_img_data.bits_per_pixel, &all->win_img_data.line_length,
							&all->win_img_data.endian);
	while (ray_count < Win_x)
	{
		adjust_dx_dy(&all->comp, all->player.ray.angle, all->player.x, all->player.y);
		adjust_tile_step(&all->comp, all->player.ray.angle);
		all->player.ray.distance = ray_distance(all);
		all->comp.height_wall = ((float)(Win_y * Field) / 2) / all->player.ray.distance;
		if (all->comp.height_wall >= Win_y || (int)all->player.ray.distance == 0)
			all->comp.height_wall = Win_y;
		all->comp.half_height_wall = all->comp.height_wall / 2;
		draw_line(&all->win_img_data, ray_count, 0, all->half_win_y - all->comp.half_height_wall, 7293925);
		y_win = all->half_win_y - all->comp.half_height_wall;
		while (y_win < all->half_win_y + all->comp.half_height_wall)
		{
			if (all->comp.pic_y >= 1920)
				all->comp.pic_y = 1919;
			my_mlx_pixel_put(&all->win_img_data, ray_count,  y_win, get_color(&all->imgs_wall[all->comp.wall_index].data, all->comp.pic_x, all->comp.pic_y));
			y_win++;
			all->comp.pic_y += all->comp.pic_y_step;
		}
		draw_line(&all->win_img_data, ray_count,  all->half_win_y + all->comp.half_height_wall, Win_y, 12043420);
		ray_count += 1;
		decreament_in_range(360, ((double)Fov / (double)Win_x), &all->player.ray.angle);
	}
	mlx_put_image_to_window(all->mlx, all->win, all->win_img_data.img, 0, 0);
}

