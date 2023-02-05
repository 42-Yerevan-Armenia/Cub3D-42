/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 11:00:37 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/05 13:17:42 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

int	get_color(t_data *data, int x, int y)
{
	char	*dst;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(int *)dst);
}