/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_dx_dy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:10:21 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/14 17:10:31 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	adjust_dx_dy(t_component *comp, double angle, double x, double y)
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
