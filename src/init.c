/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:26:19 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/15 18:42:58 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	init(t_all *all)
{
	all->identifier = malloc(sizeof(char *) * 16);
	ft_memset(all->identifier, 0, sizeof(char *) * 16);
	all->win_img_data.img = NULL;
	all->half_win_y = Win_y / 2;
	all->half_fov = Fov / 2;
	return (0);
}
