/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_tile_step.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:05:21 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/05 17:05:35 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "cub.h"

 void	adjust_tile_step(t_component *comp, double angle)
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
