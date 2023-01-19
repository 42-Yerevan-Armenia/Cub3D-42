/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_to_integer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:24:37 by vaghazar          #+#    #+#             */
/*   Updated: 2023/01/19 15:32:17 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void ft_to_integer(t_component *comp, int x, int y, int angle)
{
	if (angle >= 90 && angle <= 270)
		comp->x_int_wall = x;
	else
		comp->x_int_wall = x + 1;
	if (angle >= 0 && angle <= 180)
		comp->y_int_wall = y - 1;
	else
		comp->y_int_wall = y;
}
