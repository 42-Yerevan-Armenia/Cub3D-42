/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:10:04 by arakhurs          #+#    #+#             */
/*   Updated: 2023/01/25 20:23:03 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	ft_get_data_addr(t_all *all)
{
	if (!(all->img.n_wall || all->img.s_wall || all->img.e_wall || all->img.w_wall))
	{
		free(all->mlx);
		ft_error("❌ Can't Open Wall 🚧 Texture");
	}
	all->player.addr[2] = mlx_get_data_addr(all->img.n_wall, &all->player.bits_per_pixel[2],
			&all->player.line_length[2], &all->player.endian[2]);
	all->player.addr[3] = mlx_get_data_addr(all->img.s_wall, &all->player.bits_per_pixel[3],
			&all->player.line_length[3], &all->player.endian[3]);
	all->player.addr[4] = mlx_get_data_addr(all->img.e_wall, &all->player.bits_per_pixel[4],
			&all->player.line_length[4], &all->player.endian[4]);
	all->player.addr[5] = mlx_get_data_addr(all->img.w_wall, &all->player.bits_per_pixel[5],
			&all->player.line_length[5], &all->player.endian[5]);
}

void	ft_textures(t_all *all)
{
	int		i;
	char	*tmp;

	i = 64;
	tmp = all->img.n_wall;
	all->img.n_wall = mlx_xpm_file_to_image(all->mlx, all->img.n_tx, &i, &i);
	if ((all->img.n_wall) == NULL)
		ft_error("❌ Can't Open N_Wall 🚧 Texture");
	free(tmp);
	tmp = all->img.s_wall;
	all->img.s_wall = mlx_xpm_file_to_image(all->mlx, all->img.s_tx, &i, &i);
	if ((all->img.s_wall) == NULL)
		ft_error("❌ Can't Open S_Wall 🚧 Texture");
	free(tmp);
	tmp = all->img.e_wall;
	all->img.e_wall = mlx_xpm_file_to_image(all->mlx, all->img.e_tx, &i, &i);
	if ((all->img.e_wall) == NULL)
		ft_error("❌ Can't Open E_Wall 🚧 Texture");
	free(tmp);
	tmp = all->img.w_wall;
	all->img.w_wall = mlx_xpm_file_to_image(all->mlx, all->img.w_tx, &i, &i);
	if ((all->img.w_wall) == NULL)
		ft_error("❌ Can't Open W_Wall 🚧 Texture");
	free(tmp);
	ft_get_data_addr(all);
}