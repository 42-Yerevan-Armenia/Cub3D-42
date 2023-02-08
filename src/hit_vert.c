/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_vert.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:28:20 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/06 17:29:08 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_hit_vert(t_all *all)
{
	if (all->player.ray.angle >= 0 && all->player.ray.angle <= 180)
	{
		while((all->comp.y_intercept > (all->comp.y_int_wall * Field)))
		{
			if (all->map.map[(int)all->comp.y_intercept / Field][(int)all->comp.x_int_wall + all->comp.x_tile_wall] != '0')
				return (VERT);
			all->comp.x_int_wall += all->comp.tile_step_x;
			all->comp.y_intercept += (all->comp.y_step * all->comp.tile_step_y);
		}
	}
	else
	{
		while((all->comp.y_intercept < (all->comp.y_int_wall * Field)))
		{
			if (all->map.map[(int)all->comp.y_intercept / Field][(int)all->comp.x_int_wall + all->comp.x_tile_wall] != '0')
				return (VERT);
			all->comp.x_int_wall += all->comp.tile_step_x;
			all->comp.y_intercept += (all->comp.y_step * all->comp.tile_step_y);
		}
	}
	return (0);
}
