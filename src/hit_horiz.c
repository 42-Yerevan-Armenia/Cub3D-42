/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_horiz.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:27:36 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/06 17:29:15 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_hit_horiz(t_all *all)
{
	if (all->player.ray.angle >= 90 && all->player.ray.angle <= 270)
	{
		while((all->comp.x_intercept > all->comp.x_int_wall * Field))
		{
			if (all->map.map[(int)all->comp.y_int_wall +  all->comp.y_tile_wall][(int)all->comp.x_intercept / Field] != '0')
				return (HORIZ);
			all->comp.y_int_wall += all->comp.tile_step_y;
			all->comp.x_intercept += (all->comp.x_step * all->comp.tile_step_x);
		}
	}
	else
	{
		while(all->comp.x_intercept < all->comp.x_int_wall * Field)
		{
			if (all->map.map[(int)all->comp.y_int_wall + all->comp.y_tile_wall][(int)all->comp.x_intercept / Field] != '0')
				return (HORIZ);
			all->comp.y_int_wall += all->comp.tile_step_y;
			all->comp.x_intercept += (all->comp.x_step * all->comp.tile_step_x);
		}
	}
	return (0);
}