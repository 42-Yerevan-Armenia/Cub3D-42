/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:25:33 by arakhurs          #+#    #+#             */
/*   Updated: 2023/02/07 17:12:19 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	ft_destroy(t_all *all)
{
	mlx_destroy_window(all->mlx, all->win);
	//mlx_destroy_image(all->mlx, all->img->wall);
	sound_stop(all, 1);
	exit(EXIT_SUCCESS);
}

int	ft_close(t_all *all)
{
	mlx_destroy_window(all->mlx, all->win);
	exit(0);
	return (0);
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

int	main(int ac, char **av)
{
	t_all 	all;
	int		i;

	i = 0;
	if (ac == 2)
	{
		all.identifier = malloc(sizeof(char *) * 16);
		ft_memset(all.identifier, 0, sizeof(char *) * 16);
		ft_matrix(&all, av[1]);
		set_identifers(&all);
		all.mlx =  mlx_init();
		all.win = mlx_new_window(all.mlx, Win_x, Win_y, "cub3d");
		if (valid_identifiers(all.identifier) == 1
			&& ft_fprintf(2, "❌ Error : invalid identifier\n"))
			exit (1);
		ft_textur_path(&all);
		ft_textures(&all);
		init(&all);
		
		// sound_init(&all);
		// sound_play(&all, Sound_I, 0);
		// sound_play(&all, Sound_D1, 1);
		
		event_listener(&all);
		ray_casting(&all);
		mlx_hook(all.win, 17, 1L << 17, ft_close, &all);
		mlx_loop(all.mlx);
	}
	return 0;
}
