/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:25:33 by arakhurs          #+#    #+#             */
/*   Updated: 2023/02/02 20:05:28 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	ft_destroy(t_all *all)
{
	mlx_destroy_window(all->mlx, all->win);
	mlx_destroy_image(all->mlx, all->img.n_wall);
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
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
}

void	 render(t_all *all)
{
	double		ray_angle = all->player.p_a - (Fov / 2);
	int			ray_count = 0;
	double 		i = 0;

	ft_map_render(all);
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
		{
			int m = my_mlx_pixel_put(all, ray_count, i++, *all->player.addr[2]);
			mlx_pixel_put(all->mlx, all->win, ray_count, i++, m);
		}
		ray_count++;
		ray_angle += ((double)Fov / 1000.0);
	}
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

int	main(int ac, char **av)
{
	t_all	all;
	int		i;

	i = 0;
	if (ac == 2)
	{	
		ft_init(&all);
		all.identifier = malloc(sizeof(char *) * 16);
		ft_memset(all.identifier, 0, sizeof(char *) * 16);
		ft_matrix(&all, av[1]);
		set_identifers(&all);
		if (valid_identifiers(all.identifier) == 1
			&& ft_fprintf(2, "Error : invalid identifier\n"))
			exit (1);
		ft_textur_path(&all);
		
		// sound_init(&all);
		// sound_play(&all, Sound_I, 0);
		// sound_play(&all, Sound_D1, 1);
		
		all.player.pdx = cos(degree_to_radians(all.player.p_a));
		all.player.pdy = -1 * sin(degree_to_radians(all.player.p_a));
		all.player.ray.x = cos(degree_to_radians(all.player.p_a));
		all.player.ray.y = -1 * sin(degree_to_radians(all.player.p_a));
		ft_win(&all);
		render(&all);
		mlx_hook(all.win, 17, 0, ft_destroy, &all);
		mlx_hook(all.win, 2, 0, ft_key_press, &all);
		mlx_loop(all.mlx);
	}
	return 0;
}
