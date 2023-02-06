/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:53:03 by arakhurs          #+#    #+#             */
/*   Updated: 2023/01/31 19:23:06 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

double degree_to_radians(double a)
{
	return (a * (PI / 180));
}

double	replace_angle_360(double a)
{
	if (a >= 360)
		a = a - 360;
	else if (a <= -1)
		a = a + 360;
	return (a);
}

void	pov(t_all *all)
{
	if (all->player.p_in_map == 'E')
		all->player.p_a = 0;
	else if (all->player.p_in_map == 'N')
		all->player.p_a = 90;
	else if (all->player.p_in_map == 'W')
		all->player.p_a = 180;
	else if (all->player.p_in_map == 'S')
		all->player.p_a = 270;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

double	calc_dist(t_ray *ray)
{
	double	x;

	x = cos(degree_to_radians(ray->a)) * (ray->r_x - ray->x)
		- sin(degree_to_radians(ray->a)) * (ray->r_y - ray->y);
	return (x);
}

void	ft_vertical_dist_check(t_all *all, char c)
{
	all->player.dist = calc_dist(&all->player.ray);
	all->player.zeros = all->player.ray.zeros;
	all->player.ray.depth = Win_x;
}
