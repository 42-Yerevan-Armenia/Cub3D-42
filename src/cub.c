/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:25:33 by arakhurs          #+#    #+#             */
/*   Updated: 2023/01/25 20:26:49 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	ft_destroy(t_all *all)
{
	mlx_destroy_window(all->mlx, all->win);
	//mlx_destroy_image(all->mlx, all->img.wall);
	sound_stop(all, 1);
	exit(EXIT_SUCCESS);
}

void	ft_win(t_all *all)
{
	all->mlx = mlx_init();
	if (all->mlx == NULL)
		ft_error("❌ Can't do it 🤣");
	ft_textures(all);
	all->win = mlx_new_window(all->mlx, Win_x, Win_y, "Title");
	if (all->win == NULL)
		ft_error("❌ Can't Creat Window 📺");
	mlx_hook(all->win, 17, 0, ft_destroy, all);
}

void fill_back(void *mlx, void *mlx_win)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (i < Win_x)
	{
		while(j < Win_y / 2)
			mlx_pixel_put(mlx, mlx_win, i, j++, 0x87CEEB);

		i++;
		j = 0;
	}
	i = 0;
	j = Win_y / 2;
	while (i < Win_x)
	{
		while(j >= Win_y / 2 && j < Win_y)
			mlx_pixel_put(mlx, mlx_win, i, j++, 0x228B22);
		i++;
		j = Win_y / 2;
	}
}

void	ft_free_matrix(char ***m)
{
	int	i;

	if (!m || !*m)
		return ;
	i = 0;
	while ((*m)[i])
	{
		ft_free_array(*m + i);
		i++;
	}
	free(*m);
	*m = NULL;
}

//1. put pixel in img
//2. printf %f

void	 render(t_all *all)
{
	double		ray_angle = all->player.p_a - (Fov / 2);
	int			ray_count = 0;
	double 		i = 0;

	fill_back(all->mlx, all->win);
	while (ray_count < Win_x)
	{
		all->player.ray.x = all->player.x;
		all->player.ray.y = all->player.y;
		all->player.ray.r_cos = cos(degree_to_radians(ray_angle)) / 64;
		all->player.ray.r_sin = sin(degree_to_radians(ray_angle)) / 64;
		all->player.ray.x += all->player.ray.r_cos;
		all->player.ray.y += all->player.ray.r_sin;
		while (all->map.map[(int)floor(all->player.ray.y)][(int)floor(all->player.ray.x)] != '1')
		{//floor -> kloracnel
			all->player.ray.x += all->player.ray.r_cos;
			all->player.ray.y += all->player.ray.r_sin;
		}//pow -> x^y, sqrt -> x^2
		all->player.ray.distance = sqrt(pow(all->player.x - all->player.ray.x, 2) + pow(all->player.y - all->player.ray.y, 2));
		all->player.ray.distance = all->player.ray.distance * cos(degree_to_radians(ray_angle - all->player.p_a));
		all->player.ray.h = floor(((float)Win_y / 2) / all->player.ray.distance);
		i = (Win_y / 2) - all->player.ray.h;
		while (i < (Win_y / 2) + all->player.ray.h)
			mlx_pixel_put(all->mlx, all->win, ray_count, i++, 0x778899);
		ray_count++;
		ray_angle += ((double)Fov / 1000.0);
	}
}

void	ft_map_render(t_all *all)
{
	if (all->img.img)
		mlx_destroy_image(all->mlx, all->img.img);
	all->img.img = mlx_new_image(all->mlx, Win_x, Win_y);
	if (!all->img.img)
		ft_error("❌ NO IMG 🏞\n");
	all->player.addr[1] = mlx_get_data_addr(all->img.img, &all->player.bits_per_pixel[1],
						&all->player.line_length[1], &all->player.endian[1]);
	raycast(all);
	// mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
}

void	put_pixel(t_all *a, int x, int y, int clr)
{
	char	*dst;

	dst = a->player.addr[1] + ((y * a->player.line_length[0])
			+ x * (a->player.bits_per_pixel[0] / 8));
	*(unsigned int *)dst = clr;
}

void	ft_wall_minimap(t_all *all, int x, int y, int k)
{
	int	j;
	int	i;

	i = 0;
	while (i <= Win_x / 50)
	{
		j = 0;
		while (j <= Win_y / 50)
		{
			if (i == 0 || j == 0)
				put_pixel(all, i + x * Win_x / 50,
					j + y * Win_y / 50, 0x0FF000000);
			else
				put_pixel(all, i + x * Win_x / 50,
					j + y * Win_y / 50, k);
			j++;
		}
		i++;
	}
}

void	ft_player_minimap(t_all *all, double x, double y)
{
	double	j;
	double	i;

	i = 0.5 - Win_x / 250;
	while (i <= Win_x / 250)
	{
		j = 0.5 - Win_y / 250;
		while (j <= Win_x / 250)
		{
			put_pixel(all, i + x * Win_x / 50,
				j + y * Win_y / 50, 0xff110211);
			j++;
		}
		i++;
	}
}

void	ft_player_init(t_all *all)
{
	double	x;
	double	y;

	if (all->player.x < 5)
		x = all->player.x;
	else if (all->map.x - all->player.x < 5)
		x = 10 - (all->map.x - all->player.x);
	else
		x = 4 + (all->player.x - (int)all->player.x);
	if (all->player.y < 5)
		y = all->player.y;
	else if (all->player.h - all->player.y < 5)
		y = 10 - (all->player.h - all->player.y);
	else
		y = 5 + (all->player.y - (int)all->player.y);
	ft_player_minimap(all, x, y);
}

void	ft_sub_minimap(t_map *map, t_all *all, double x)
{
	int		i;
	int		j;
	char	*line;

	j = 0;
	while (map && j < 10)
	{
		line = *map->map;
		i = 0;
		while (line[(int)x + i] && i < 10)
		{
			if (line[(int)x + i] == '1')
				ft_wall_minimap(all, i, j, 0x2202f2);
			else if (line[(int)x + i] == '_')
				ft_wall_minimap(all, i, j, 0x038a30);
			else
				ft_wall_minimap(all, i, j, 0x00000000);
			i++;
		}
		j++;
		// map = map->map;
	}
	ft_player_init(all);
}

void	render_minimap(t_map *map, t_all *all)
{
	double	x;
	double	y;

	if (all->map.minimap)
		mlx_destroy_image(all->mlx, all->map.minimap);
	all->map.minimap = mlx_new_image(all->mlx, Win_x / 5, Win_y / 5);
	all->player.addr[1] = mlx_get_data_addr(all->map.minimap, &all->player.bits_per_pixel[0],
		&all->player.line_length[0], &all->player.endian[0]);
	y = 0;
	while (all->player.h < 11 && all->player.y > y + 6 && all->player.h > y + 10)
	{
		// map = map->map;
		y++;
	}
	if (all->map.x < 11 || all->player.x <= 4)
		x = 0;
	else if (all->map.x - all->player.x <= 6)
		x = all->map.x - 10;
	else
		x = all->player.x - 4;
	ft_sub_minimap(map, all, x);
	mlx_put_image_to_window(all->mlx, all->win, all->map.minimap, 0, 0);
}


int	loop_hook(t_all *all)
{
	ft_map_render(all);
	//render_minimap(&all->map, all);
	return (0);
}

void	ft_textur_path(t_all *all)
{
	all->img.n_wall = NULL;
	all->img.s_wall = NULL;
	all->img.e_wall = NULL;
	all->img.w_wall = NULL;
	all->img.n_tx = get_identifier(all->identifier, "NO");
	all->img.s_tx = get_identifier(all->identifier, "SO");
	all->img.e_tx = get_identifier(all->identifier, "EA");
	all->img.w_tx = get_identifier(all->identifier, "WE");
	
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
	
}

int	main(int ac, char **av)
{
	t_all	all;
	int		i;

	i = 0;
	if (ac == 2)
	{	
		all.identifier = malloc(sizeof(char *) * 16);
		ft_memset(all.identifier, 0, sizeof(char *) * 16);
		ft_matrix(&all, av[1]);
		set_identifers(&all);
		if (valid_identifiers(all.identifier) == 1
			&& ft_fprintf(2, "Error : invalid identifier\n"))
			exit (1);
		ft_textur_path(&all);
		//sound_init(&all);
		//sound_play(&all, Sound_D1, 1);
		all.player.pdx = cos(degree_to_radians(all.player.p_a));
		all.player.pdy = -1 * sin(degree_to_radians(all.player.p_a));
		all.player.ray.x = cos(degree_to_radians(all.player.p_a));
		all.player.ray.y = -1 * sin(degree_to_radians(all.player.p_a));
		ft_win(&all);
		// ft_textures(&all);
		render(&all);
		mlx_hook(all.win, 17, 0, ft_destroy, &all);
		mlx_hook(all.win, 2, 0, ft_key_press, &all);
		mlx_loop_hook(all.mlx, &loop_hook, &all);
		mlx_loop(all.mlx);
	}
	return 0;
}
