/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decreament_in_range.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:32:43 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/05 10:07:35 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void decreament_in_range(double range, double step, double *num)
{
	if (/*(int)*/(*num) - step >= 0)
		*num -= step;
	else
		*num = *num + range - step;
}
