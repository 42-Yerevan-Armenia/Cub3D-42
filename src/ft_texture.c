/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:10:04 by arakhurs          #+#    #+#             */
/*   Updated: 2023/02/15 21:39:19 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static int	check_chars(char *c, t_all *all)
{
	int	i;
	int	j[1];

	i = 0;
	j[0] = 0;
	while (c[i] != '\0')
	{
		if (c[i] == ',')
		{
			j[0]++;
			i++;
		}
		if (!(c[i] >= '0' && c[i] <= '9'))
			return (1);
		i++;
	}
	if ((j[0] != 2))
		ft_error(all, "❌ Less ','❗️");
	return (0);
}

static void	set_rgb(t_rgb *rgb, char *color, t_all *all)
{
	char	**c;

	if (check_chars(color, all))
		ft_error(all, "❌RGB must be numeric");
	c = ft_split(color, ',');
	rgb->r = ft_atoi(c[0]);
	if (rgb->r <= -1 || rgb->r >= 256)
		ft_error(all, "❌ Not correct R of rgb");
	rgb->g = ft_atoi(c[1]);
	if (rgb->g <= -1 || rgb->g >= 256)
		ft_error(all, "❌ Not correct G of rgb");
	rgb->b = ft_atoi(c[2]);
	if (rgb->b <= -1 || rgb->b >= 256)
		ft_error(all, "❌ Not correct B of rgb");
	rgb->val = (rgb->r << 16) | (rgb->g << 8) | rgb->b;
	ft_free_double(&c);
}

void	ft_textur_path(t_all *all)
{
	all->img.n_tx = get_identifier(all->identifier, "NO");
	all->img.s_tx = get_identifier(all->identifier, "SO");
	all->img.e_tx = get_identifier(all->identifier, "EA");
	all->img.w_tx = get_identifier(all->identifier, "WE");
	all->img.floor.f_tx = get_identifier(all->identifier, "F");
	all->img.ceil.c_tx = get_identifier(all->identifier, "C");
	if (ft_strlen(all->img.n_tx) < 5 || ft_strcmp(".xpm", \
		(char *)all->img.n_tx + (ft_strlen(all->img.n_tx) - 4)) != 0)
		ft_error(all, "❌ Texture format is not *.xpm");
	if (ft_strlen(all->img.s_tx) < 5 || ft_strcmp(".xpm", \
		(char *)all->img.s_tx + (ft_strlen(all->img.s_tx) - 4)) != 0)
		ft_error(all, "❌ Texture format is not *.xpm");
	if (ft_strlen(all->img.e_tx) < 5 || ft_strcmp(".xpm", \
		(char *)all->img.e_tx + (ft_strlen(all->img.e_tx) - 4)) != 0)
		ft_error(all, "❌ Texture format is not *.xpm");
	if (ft_strlen(all->img.w_tx) < 5 || ft_strcmp(".xpm", \
		(char *)all->img.w_tx + (ft_strlen(all->img.w_tx) - 4)) != 0)
		ft_error(all, "❌ Texture format is not *.xpm");
	if (!(ft_strlen(all->img.floor.f_tx) > 4 && \
		ft_strlen(all->img.floor.f_tx) < 12))
		ft_error(all, "❌ Floor RGB format is not correct");
	if (!(ft_strlen(all->img.ceil.c_tx) > 4 && \
		ft_strlen(all->img.ceil.c_tx) < 12))
		ft_error(all, "❌ Ceil RGB format is not correct");
	ft_textures(all);
}

static void	ft_textures_minimap(t_all *all)
{
	int		w;
	int		h;

	all->img.wall_tx = mlx_xpm_file_to_image(all->mlx, WALL, &w, &h);
	if ((all->img.wall_tx) == NULL)
		ft_error(all, "❌ Can't Open Wall 🚧 Texture");
	all->img.floor_tx = mlx_xpm_file_to_image(all->mlx, FLOOR, &w, &h);
	if (all->img.floor_tx == NULL)
		ft_error(all, "Cant Open Floor 🚧  Texture");
	all->img.space_tx = mlx_xpm_file_to_image(all->mlx, SP, &w, &h);
	if (all->img.space_tx == NULL)
		ft_error(all, "Cant Open Space 🚧  Texture");
	all->img.player_tx = mlx_xpm_file_to_image(all->mlx, PLAYER, &w, &h);
	if ((all->img.player_tx) == NULL)
		ft_error(all, "❌ Can't Open Player 🚧 Texture");
}

void	ft_textures(t_all *all)
{
	int		w;
	int		h;

	ft_textures_minimap(all);
	all->img.n_wall = mlx_xpm_file_to_image(all->mlx, all->img.n_tx, &w, &h);
	if ((all->img.n_wall) == NULL)
		ft_error(all, "❌ Can't Open N_Wall 🚧 Texture");
	all->img.s_wall = mlx_xpm_file_to_image(all->mlx, all->img.s_tx, &w, &h);
	if ((all->img.s_wall) == NULL)
		ft_error(all, "❌ Can't Open S_Wall 🚧 Texture");
	all->img.e_wall = mlx_xpm_file_to_image(all->mlx, all->img.e_tx, &w, &h);
	if ((all->img.e_wall) == NULL)
		ft_error(all, "❌ Can't Open E_Wall 🚧 Texture");
	all->img.w_wall = mlx_xpm_file_to_image(all->mlx, all->img.w_tx, &w, &h);
	if ((all->img.w_wall) == NULL)
		ft_error(all, "❌ Can't Open W_Wall 🚧 Texture");
	set_rgb(&all->img.floor, all->img.floor.f_tx, all);
	if ((all->img.floor.f_tx) == NULL)
		ft_error(all, "❌ Can't set RGB 🎨 color");
	set_rgb(&all->img.ceil, all->img.ceil.c_tx, all);
	if ((all->img.ceil.c_tx) == NULL)
		ft_error(all, "❌ Can't set RGB 🎨 color");
}
