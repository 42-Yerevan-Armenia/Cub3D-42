/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:26:08 by vaghazar          #+#    #+#             */
/*   Updated: 2023/01/16 17:26:34 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	event(int key, void *param)
{
	t_all *all;

	all = param;
	if (key == KEY_W)
	{
		all->player.y += sin(degree_to_radians(all->player.angle));
		all->player.x += cos(degree_to_radians(all->player.angle));
	}
	if (key == KEY_S)
	{
		all->player.y -= sin(degree_to_radians(all->player.angle));
		all->player.x -= cos(degree_to_radians(all->player.angle));
	}
	ray_casting(all);
	return (0);
}

void event_listener(t_all *all)
{
	mlx_key_hook(all->win, &event, all);
}
