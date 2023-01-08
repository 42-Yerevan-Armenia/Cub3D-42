/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:25:33 by arakhurs          #+#    #+#             */
/*   Updated: 2023/01/08 20:11:44 by arakhurs         ###   ########.fr       */
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
	all->win = mlx_new_window(all->mlx, 1800, 1024, "Title");
	if (all->win == NULL)
		ft_error("❌ Can't Creat Window 📺");
	all->img.img = mlx_new_image(all->mlx, 1800, 1024);
	mlx_hook(all->win, 17, 0, ft_destroy, all);
}

int	ft_key_press(int keycode, t_all *all)
{
	//char	c;
	if (keycode == 53)
		ft_destroy(all);
	return (0);
}

void	ft_textures(t_img *img, void *mlx)
{
	int	width;
	int	height;

	img->wall = mlx_xpm_file_to_image(mlx, WALL, &width, &height);
	if ((img->wall) == NULL)
		ft_error("❌ Can't Open Wall 🚧 Texture");
}

int	main(int ac, char **av)
{
	t_all	all;
	int		i;

	// char	(*idendifier)[13];
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
		sound_init(&all);
		sound_play(&all, Sound_D1, 1);
		ft_win(&all);
		ft_textures(&all.img, all.mlx);
		mlx_hook(all.win, 2, 0, ft_key_press, &all);
		//mlx_loop_hook(all.mlx, &loop_hook, &a);
		mlx_loop(all.mlx);
	}
	return 0;
}
