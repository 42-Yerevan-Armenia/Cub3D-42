/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:16:42 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/16 20:03:24 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	draw_walls(t_all *all, int ray_count)
{
	int	y_win;

	y_win = all->half_win_y - all->comp.half_h_wall;
	while (y_win < all->half_win_y + all->comp.half_h_wall)
	{
		my_mlx_pixel_put(&all->win_img_data, ray_count, y_win,
			get_color(&all->imgs_wall[all->comp.wall_index].data,
				all->comp.pic_x, all->comp.pic_y));
		y_win++;
		all->comp.pic_y += all->comp.pic_y_step;
	}
}

static void	draw_line(t_data *win_img_data, int x, t_line *line)
{
	while (line->start_y < line->end_y)
	{
		my_mlx_pixel_put(win_img_data, x, line->start_y, line->color);
		line->start_y++;
	}
}

static void	init_line(t_line *line, int start_y, int end_y, int color)
{
	line->color = color;
	line->end_y = end_y;
	line->start_y = start_y;
}

void	draw_img(t_all *all, int ray_count)
{
	init_line(&all->line, 0, all->half_win_y
		- all->comp.half_h_wall, all->img.ceil.val);
	draw_line(&all->win_img_data, ray_count, &all->line);
	draw_walls(all, ray_count);
	init_line(&all->line, all->half_win_y
		+ all->comp.half_h_wall, Win_y, all->img.floor.val);
	draw_line(&all->win_img_data, ray_count, &all->line);
}

int	valid_key(int key)
{
	if (key == KEY_W || key == KEY_S || key == KEY_A
		|| key == KEY_D || key == KEY_ARROW_LEFT
		|| key == KEY_ARROW_RIGHT || key == KEY_ESC
		|| key == KEY_M)
		return (1);
	return (0);
}
