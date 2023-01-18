/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:06:37 by arakhurs          #+#    #+#             */
/*   Updated: 2023/01/18 18:44:17 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

#define SPEED 2
#define SPEED_D 5

void	ft_move_right(t_all *a)
{
char c = a->map.map[(int)a->player.y + 1][(int)a->player.x];
	if(c && c != '1')
	{
		a->player.y += 0.1;
		a->map.map[(int)a->player.y - 1][(int)a->player.x] = '0';
		a->map.map[(int)a->player.y][(int)a->player.x] = 'W';
		render(a);
	}
}

void	ft_move_left(t_all *a)
{
	char c = a->map.map[(int)a->player.y - 1][(int)a->player.x];
	if(c && c != '1')
	{
		a->player.y -= 0.1;
		a->map.map[(int)a->player.y + 1][(int)a->player.x] = '0';
		a->map.map[(int)a->player.y][(int)a->player.x] = 'W';	
		render(a);
	}
}

void	ft_move_up(t_all *a)
{
	char c = a->map.map[(int)a->player.y][(int)a->player.x + 1];
	if(c && c != '1')
	{
		a->map.map[(int)a->player.y][(int)a->player.x] = '0';
		a->map.map[(int)a->player.y][(int)a->player.x + 1] = 'W';
		a->player.x += 0.1;
		render(a);
	}
}

void	ft_move_down(t_all *a)
{
	char c = a->map.map[(int)a->player.y][(int)a->player.x - 1];
	if(c && c != '1')
	{
		a->map.map[(int)a->player.y][(int)a->player.x - 1] = '0';
		a->map.map[(int)a->player.y][(int)a->player.x] = 'W';
		a->player.x -= 0.1;
		render(a);
	}
}
