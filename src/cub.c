/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:25:33 by arakhurs          #+#    #+#             */
/*   Updated: 2023/01/18 18:36:45 by arakhurs         ###   ########.fr       */
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
	all->win = mlx_new_window(all->mlx, Win_x, Win_y, "Title");
	if (all->win == NULL)
		ft_error("❌ Can't Creat Window 📺");
	all->img.img = mlx_new_image(all->mlx, Win_x, Win_y);
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
			mlx_pixel_put(mlx, mlx_win, i, j++, 0x00FF0000);
		i++;
		j = 0;
	}
	i = 0;
	j = Win_y / 2;
	while (i < Win_x)
	{
		while(j >= Win_y / 2 && j < Win_y)
			mlx_pixel_put(mlx, mlx_win, i, j++, 0x0000FF00);
		i++;
		j = Win_y / 2;
	}
}

void	 render(t_all *all)
{

	double		ray_angle = all->player.angle - (Fov / 2);
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
		while (all->map.map[(int)floor(all->player.ray.x)][(int)floor(all->player.ray.y)] != '1')
		{//floor -> kloracnel
			all->player.ray.x += all->player.ray.r_cos;
			all->player.ray.y += all->player.ray.r_sin;
		}//pow -> x^y, sqrt -> x^2

		all->player.ray.distance = sqrt(pow(all->player.x - all->player.ray.x, 2) + pow(all->player.y - all->player.ray.y, 2));
		all->player.ray.distance = all->player.ray.distance * cos(degree_to_radians(ray_angle - all->player.angle));
		all->player.ray.h = floor(((float)Win_y / 2) / all->player.ray.distance);
		i = (Win_y / 2) - all->player.ray.h;
		while (i < (Win_y / 2) + all->player.ray.h)
			mlx_pixel_put(all->mlx, all->win, ray_count, i++, 0x000000FF);
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
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
}

int	loop_hook(t_all *all)
{
	ft_map_render(all);
	return (0);
}

int	main(int ac, char **av)
{
	t_all	all;
	int		i;

	i = 0;
	if (ac == 2)
	{
		all.img.n_wall = NULL;
		all.img.s_wall = NULL;
		all.img.e_wall = NULL;
		all.img.w_wall = NULL;
	
		all.identifier = malloc(sizeof(char *) * 16);
		ft_memset(all.identifier, 0, sizeof(char *) * 16);
		ft_matrix(&all, av[1]);
		
		set_identifers(&all);
		if (valid_identifiers(all.identifier) == 1
			&& ft_fprintf(2, "Error : invalid identifier\n"))
			exit (1);
		//sound_init(&all);
		//sound_play(&all, Sound_D1, 1);

		all.player.ray.x = cos(degree_to_radians(all.player.p_a));
		all.player.ray.y = -1 * sin(degree_to_radians(all.player.p_a));
		
		ft_win(&all);
		ft_textures(&all);
		render(&all);
		mlx_hook(all.win, 2, 0, ft_key_press, &all);
		//mlx_loop_hook(all.mlx, &loop_hook, &all);
		mlx_loop(all.mlx);
	}
	return 0;
}
