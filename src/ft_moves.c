/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:06:37 by arakhurs          #+#    #+#             */
/*   Updated: 2023/01/29 15:00:07 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

#define SPEED 2
#define SPEED_D 5

void	ft_move_right(t_all *a)
{
	double	d = 0;
	char c = a->map.map[(int)a->player.y + 1][(int)a->player.x];
	if(c && c != '1')
	{
		printf("1\n");
		a->player.y += (a->player.pdy * 0.1);
		a->map.map[(int)a->player.y - 1][(int)a->player.x] = '0';
		a->map.map[(int)a->player.y][(int)a->player.x] = 'W';
		render(a);
	}
	else if (c && a->player.y < (int)a->player.y + 1)
	{
		printf("2\n");
		d = (int)a->player.y + 1 - a->player.y;
		a->player.y += 0.1;
		render(a);
	}
	else if (c && a->player.y > (int)a->player.y + 1)
	{
		printf("3\n");
		d = (int)a->player.y + 1 - a->player.y;
		a->player.y -= 0.1;
		render(a);
	}
	printf("➡️\n");
}

void	ft_move_left(t_all *a)
{
	double	d = 0;
	char c = a->map.map[(int)a->player.y - 1][(int)a->player.x];
	if(c && c != '1')
	{
		a->player.y -= (a->player.pdy * 0.1);
		a->map.map[(int)a->player.y + 1][(int)a->player.x] = '0';
		a->map.map[(int)a->player.y][(int)a->player.x] = 'W';
		render(a);
	}
	else if (c && a->player.y > (int)a->player.y + 1)
	{
		d = (int)a->player.y + 1 - a->player.y;
		a->player.y += 0.1;
		render(a);
	}
	else if (c && a->player.y < (int)a->player.y + 1)
	{
		d = (int)a->player.y + 1 - a->player.y;
		a->player.y -= 0.1;
		render(a);
	}
	printf("⬅️\n");
}

void	ft_move_up(t_all *a)
{
	char c = a->map.map[(int)a->player.y][(int)a->player.x + 1];
	if(c && c != '1')
	{
		a->player.x += (a->player.pdx * 0.1);
		a->player.y -= (a->player.pdy * 0.1);
		a->map.map[(int)a->player.y][(int)a->player.x] = '0';
		a->map.map[(int)a->player.y][(int)a->player.x + 1] = 'W';
		render(a);
	}
	printf("⬆️\n");
}

void	ft_move_down(t_all *a)
{
	char c = a->map.map[(int)a->player.y][(int)a->player.x - 1];
	if(c && c != '1')
	{
		a->player.x -= (a->player.pdx * 0.1);
		a->player.y += (a->player.pdy * 0.1);
		a->map.map[(int)a->player.y][(int)a->player.x - 1] = '0';
		a->map.map[(int)a->player.y][(int)a->player.x] = 'W';
		render(a);
	}
	printf("⬇️\n");
}

void	ft_view_left(t_all *a)
{
		a->player.p_a -= 5;
		a->player.angle = replace_angle_360(a->player.p_a);
		a->player.pdx = cos(degree_to_radians(a->player.p_a));
		a->player.pdy = -1 * sin(degree_to_radians(a->player.p_a));
		render(a);
}

void	ft_view_right(t_all *a)
{
		a->player.p_a += 5;
		a->player.angle = replace_angle_360(a->player.p_a);
		a->player.pdx = cos(degree_to_radians(a->player.p_a));
		a->player.pdy = -1 * sin(degree_to_radians(a->player.p_a));
		render(a);
}