/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:43:07 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/15 10:12:20 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(int *)dst = color;
}

int	get_img(t_img *img, void *mlx, char	*img_path)
{
	int	ret;

	ret = 0;
	img->img = mlx_xpm_file_to_image(mlx, img_path, &img->width, &img->height);
	if (img->img == NULL && ++ret)
		ft_fprintf(2, "Cub3d : Error : %s : %s\n", img_path, strerror(errno));
	img->data.addr = mlx_get_data_addr(img->img, &img->data.bits_per_pixel, \
	&img->data.line_length, &img->data.endian);
	if (img->data.addr == NULL && ++ret)
		ft_fprintf(2, "Cub3d : Error : %s : %s\n", img_path, strerror(errno));
	return (ret);
}

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
