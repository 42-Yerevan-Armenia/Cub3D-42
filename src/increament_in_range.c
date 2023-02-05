/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increament_in_range.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:32:24 by vaghazar          #+#    #+#             */
/*   Updated: 2023/01/27 19:50:41 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void increament_in_range(double range, double step, double *num)
{
	if ((int)(*num) + step <= range)
		*num += step;
	else
		*num = *num - range + step;
}
