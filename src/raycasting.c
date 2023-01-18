/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:36:46 by arakhurs          #+#    #+#             */
/*   Updated: 2023/01/18 18:30:30 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	v_ray_2(t_all *all)
{
	int		mx;
	int		my;
	char	val;

	while (all->player.ray.depth < Win_x)
	{
		mx = (int)all->player.ray.r_x >> 6;
		my = (int)all->player.ray.r_y >> 6;
		all->player.ray.r_x += all->player.ray.x_o;
		all->player.ray.r_y += all->player.ray.y_o;
		all->player.ray.depth += 1;
	}
	all->player.ray.v_x = all->player.ray.r_x;
	all->player.ray.v_y = all->player.ray.r_y;
}

void	v_ray(t_all *all)
{
	all->player.ray.tan_a = tan(degree_to_radians(all->player.ray.a));
	all->player.ray.depth = 0;
	if (cos(degree_to_radians(all->player.ray.a)) > 0.0001)
	{
		all->player.ray.zeros = 5;
		all->player.ray.r_x = (((int)all->player.ray.x >> 6) << 6) + 64;
		all->player.ray.r_y = (all->player.ray.x - all->player.ray.r_x) * all->player.ray.tan_a + all->player.ray.y;
		all->player.ray.x_o = 64;
		all->player.ray.y_o = -64 * all->player.ray.tan_a;
	}
	else if (cos(degree_to_radians(all->player.ray.a)) < -0.0001)
	{
		all->player.ray.zeros = 4;
		all->player.ray.r_x = (((int)all->player.ray.x >> 6) << 6) - 0.0001;
		all->player.ray.r_y = (all->player.ray.x - all->player.ray.r_x) * all->player.ray.tan_a + all->player.ray.y;
		all->player.ray.x_o = -64;
		all->player.ray.y_o = 64 * all->player.ray.tan_a;
	}
	else if (cos(degree_to_radians(all->player.ray.a)) == 0)
	{
		all->player.ray.depth = Win_x;
		all->player.ray.r_x = all->player.ray.x;
		all->player.ray.r_y = all->player.ray.y;
	}
	v_ray_2(all);
}

void	h_ray_2(t_all *all)
{
	int		mx;
	int		my;
	char	c;

	while (all->player.ray.depth <Win_y)
	{
		mx = (int)all->player.ray.r_x >> 6;
		my = (int)all->player.ray.r_y >> 6;
		all->player.ray.r_x += all->player.ray.x_o;
		all->player.ray.r_y += all->player.ray.y_o;
		all->player.ray.depth += 1;
	}
}

void	h_ray(t_all *all)
{
	all->player.ray.tan_a = 1.0 / tan(degree_to_radians(all->player.ray.a));
	all->player.ray.depth = 0;
	if (sin(degree_to_radians(all->player.ray.a)) > 0.0001)
	{
		all->player.ray.zerosh = 2;
		all->player.ray.r_y = (((int)all->player.ray.y >> 6) << 6) - 0.0001;
		all->player.ray.r_x = (all->player.ray.y - all->player.ray.r_y) * all->player.ray.tan_a + all->player.ray.x;
		all->player.ray.y_o = -64;
		all->player.ray.x_o = 64 * all->player.ray.tan_a;
	}
	else if (sin(degree_to_radians(all->player.ray.a)) < -0.0001)
	{
		all->player.ray.zerosh = 3;
		all->player.ray.r_y = (((int)all->player.ray.y >> 6) << 6) + 64;
		all->player.ray.r_x = (all->player.ray.y - all->player.ray.r_y) * all->player.ray.tan_a + all->player.ray.x;
		all->player.ray.y_o = 64;
		all->player.ray.x_o = -64 * all->player.ray.tan_a;
	}
	else if (sin(degree_to_radians(all->player.ray.a)) < 0.0001 && 
		sin(degree_to_radians(all->player.ray.a)) > -0.0001)
	{
		all->player.ray.depth =Win_y;
		all->player.ray.r_x = all->player.ray.x;
		all->player.ray.r_y = all->player.ray.y;
	}
	h_ray_2(all);
}

void	my_mlx_pixel_put(t_all *all, int x, int y, int clr)
{
	char	*dst;

	dst = all->player.addr[1] + ((y * all->player.line_length[1]) + x
			* (all->player.bits_per_pixel[1] / 8));
	*(unsigned int *)dst = clr;
}

void	put_texture_pixel(t_all *all, int x, int y, int k)
{
	char	*dst;
	int		i;
	int		j;

	if (all->player.linelen == 0)
		return ;
	i = all->player.p_r;
	k = k + all->player.stepy;
	j = (k << 6) / all->player.linelen;
	dst = all->player.addr[all->player.zeros] + ((j * all->player.line_length[all->player.zeros])
			+ i * (all->player.bits_per_pixel[all->player.zeros] / 8));
	my_mlx_pixel_put(all, x, y, *(unsigned int *)dst);
}

void	raycast(t_all *all)
{
	int	i;
	
	i = 0;
	all->player.ray.a = replace_angle_360(all->player.angle + 30);
	all->player.ray.x = all->player.p_x * 64;
	all->player.ray.y = all->player.p_y * 64;
	while (i < Win_x)
	{
		all->player.distance = 1000000;
		v_ray(all);
		h_ray(all);
		all->player.distance *= cos(degree_to_radians(replace_angle_360(all->player.angle - all->player.ray.a)));
		if (all->player.ray.zeros > 3 && all->player.ray.zeros != 6)
			all->player.p_r = (int)(all->player.ray.v_y) % 64;
		else
			all->player.p_r = (int)(all->player.ray.r_x) % 64;
		all->player.ray.a = replace_angle_360(all->player.ray.a - all->player.angle);
		i++;
	}
}
