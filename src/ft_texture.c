/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:10:04 by arakhurs          #+#    #+#             */
/*   Updated: 2023/02/07 13:27:39 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	get_color(t_data *data, int x, int y)
{
	char	*dst;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(int *)dst);
}

int get_img(t_img *img, void *mlx, char	*img_path)
{
	int	ret;

	ret = 0;
	img->img = mlx_xpm_file_to_image(mlx, img_path, &img->width, &img->height); // size - 1
	if (img->img == NULL && ++ret)
		ft_fprintf(2, "Cub3d : Error : %s : %s\n", img_path, strerror(errno));
	img->data.addr = mlx_get_data_addr(img->img, &img->data.bits_per_pixel, &img->data.line_length, &img->data.endian);
	if (img->data.addr == NULL && ++ret)
		ft_fprintf(2, "Cub3d : Error : %s : %s\n", img_path, strerror(errno));
	return (ret);
}

void	ft_textur_path(t_all *all)
{
	all->img.n_tx = get_identifier(all->identifier, "NO");
	all->img.s_tx = get_identifier(all->identifier, "SO");
	all->img.e_tx = get_identifier(all->identifier, "EA");
	all->img.w_tx = get_identifier(all->identifier, "WE");
	all->img.c_tx = get_identifier(all->identifier, "F");
	all->img.f_tx = get_identifier(all->identifier, "C");
	if (ft_strlen(all->img.n_tx) < 5
		|| ft_strcmp(".xpm", (char *)all->img.n_tx + (ft_strlen(all->img.n_tx) - 4)) != 0)
		ft_error("❌ Texture format is not *.xpm");
	if (ft_strlen(all->img.s_tx) < 5
		|| ft_strcmp(".xpm", (char *)all->img.s_tx + (ft_strlen(all->img.s_tx) - 4)) != 0)
		ft_error("❌ Texture format is not *.xpm");
	if (ft_strlen(all->img.e_tx) < 5
		|| ft_strcmp(".xpm", (char *)all->img.e_tx + (ft_strlen(all->img.e_tx) - 4)) != 0)
		ft_error("❌ Texture format is not *.xpm");
	if (ft_strlen(all->img.w_tx) < 5
		|| ft_strcmp(".xpm", (char *)all->img.w_tx + (ft_strlen(all->img.w_tx) - 4)) != 0)
		ft_error("❌ Texture format is not *.xpm");
	printf("%s, %zu\n", all->img.c_tx, ft_strlen(all->img.c_tx));
	if (!(ft_strlen(all->img.c_tx) > 4 && ft_strlen(all->img.c_tx) < 12))
		ft_error("❌ RGB format is not correct1");
	if (!(ft_strlen(all->img.f_tx) > 4 && ft_strlen(all->img.c_tx) < 12))
		ft_error("❌ RGB format is not correct2");
}

void	ft_textures(t_all *all)
{
	int		w;
	int		h;
	char	*tmp;

	tmp = all->img.n_wall;
	all->img.n_wall = mlx_xpm_file_to_image(all->mlx, all->img.n_tx, &w, &h);
	if ((all->img.n_wall) == NULL)
		ft_error("❌ Can't Open N_Wall 🚧 Texture");
	free(tmp);
	tmp = all->img.s_wall;
	all->img.s_wall = mlx_xpm_file_to_image(all->mlx, all->img.s_tx, &w, &h);
	if ((all->img.s_wall) == NULL)
		ft_error("❌ Can't Open S_Wall 🚧 Texture");
	free(tmp);
	tmp = all->img.e_wall;
	all->img.e_wall = mlx_xpm_file_to_image(all->mlx, all->img.e_tx, &w, &h);
	if ((all->img.e_wall) == NULL)
		ft_error("❌ Can't Open E_Wall 🚧 Texture");
	free(tmp);
	tmp = all->img.w_wall;
	all->img.w_wall = mlx_xpm_file_to_image(all->mlx, all->img.w_tx, &w, &h);
	if ((all->img.w_wall) == NULL)
		ft_error("❌ Can't Open W_Wall 🚧 Texture");
	free(tmp);
}