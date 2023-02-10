/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:43:07 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/07 20:22:07 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	init_img(t_all *all)
{
	if (get_img(&all->imgs_wall[0], all->mlx, all->img.w_tx)
		|| get_img(&all->imgs_wall[1], all->mlx, all->img.n_tx)
		|| get_img(&all->imgs_wall[2], all->mlx, all->img.e_tx)
		|| get_img(&all->imgs_wall[3], all->mlx, all->img.s_tx))
		return (1);
	return (0);
}

int	init(t_all *all)
{
	if (init_img(all) == 1)
	{
		exit (1);
	}
	all->win_img_data.img = NULL;
	all->half_win_y = Win_y / 2;
	all->half_fov = Fov / 2;
	return (0);
}