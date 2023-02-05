/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:06:22 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/05 17:06:35 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	field_len(double intercept, t_component *comp, int img_height, int flag)
{
	double	tmp;
	if (is_odd_wall(intercept))
		tmp = intercept - ((int)(intercept / Field) * Field);
	else
		tmp = (((int)(intercept / Field) + 1) * Field) - intercept;
	// if (flag == START_LEFT)
	comp->pic_x = tmp * (double)((double)img_height / (double)Field);
	if ((int)comp->height_wall > Win_y)
	{
		comp->pic_y = (((double)(comp->height_wall) - (double)Win_y) / (double)2) * ((double)img_height / (double)comp->height_wall);
		comp->pic_y_step = (img_height -  (comp->pic_y  * 2)) / Win_y;
	}
	else
	{
		comp->pic_y = 0;
		comp->pic_y_step = (((double)img_height) / (comp->height_wall));
	}
}