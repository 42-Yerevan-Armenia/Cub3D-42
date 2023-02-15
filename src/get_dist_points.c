/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dist_points.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:57:56 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/15 18:46:15 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

double	get_dist_points(double p1_x, double p1_y, double p2_x, double p2_y)
{
	return (sqrt(ft_fabs((p1_x - p2_x) * (p1_x - p2_x))
			+ ft_fabs((p1_y - p2_y) * (p1_y - p2_y))));
}
