/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:40:29 by arakhurs          #+#    #+#             */
/*   Updated: 2023/02/15 10:16:12 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

double	pov(char c)
{
	if (c == 'N')
		return (90.0);
	if (c == 'S')
		return (270.0);
	if (c == 'E')
		return (0.0);
	if (c == 'W')
		return (180.0);
	return (0.0);
}

double	d_to_rdn(double a)
{
	return (a * (PI / 180));
}

double	ft_fabs(double a)
{
	if (a < 0)
		return (-a);
	return (a);
}

void	decreament_in_range(double range, double step, double *num)
{
	if ((*num) - step >= 0)
		*num -= step;
	else
		*num = *num + range - step;
}

void	increament_in_range(double range, double step, double *num)
{
	if ((int)(*num) + step <= range)
		*num += step;
	else
		*num = *num - range + step;
}
