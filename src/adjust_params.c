/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:17:09 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/15 19:20:49 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	adjust_tile_step(t_component *comp, double angle)
{
	if (angle >= 90 && angle <= 270)
		comp->tile_step_x = -1;
	else
		comp->tile_step_x = 1;
	if (angle >= 0 && angle <= 180)
		comp->tile_step_y = -1;
	else
		comp->tile_step_y = 1;
}

static void	adjust_dx_dy(t_component *comp, double angle, double x, double y)
{
	if (angle >= 90 && angle <= 270)
		comp->dx = ft_fabs((((int)x / Field) * Field) - x);
	else
		comp->dx = ft_fabs((((((int)(x / Field)) * Field) + Field) - x));
	if (angle >= 0 && angle <= 180)
		comp->dy = ft_fabs((y - (((int)(y / Field)) * Field)));
	else
		comp->dy = ft_fabs((y - (((int)(y / Field)) * Field + Field)));
}

void	adjust_params(t_all *all)
{
	adjust_dx_dy(&all->comp, all->player.ray.angle,
		all->player.x, all->player.y);
	adjust_tile_step(&all->comp, all->player.ray.angle);
}
