/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:25:33 by arakhurs          #+#    #+#             */
/*   Updated: 2023/02/13 15:36:34 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	ft_destroy(t_all *all)
{
	mlx_destroy_window(all->mlx, all->win);
	mlx_destroy_image(all->mlx, all->img.wall_tx);
	mlx_destroy_image(all->mlx, all->img.floor_tx);
	mlx_destroy_image(all->mlx, all->img.space_tx);
	mlx_destroy_image(all->mlx, all->img.player_tx);
	sound_stop(all, 0);
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
		ft_error(all, "❌ Can't do it 🤣");
	all->win = mlx_new_window(all->mlx, 1800, 1024, "Title");
	if (all->win == NULL)
		ft_error(all, "❌ Can't Creat Window 📺");
	all->img.img = mlx_new_image(all->mlx, 1800, 1024);
	mlx_hook(all->win, 17, 0, ft_destroy, all);
}

void	draw_minimap(t_all *all)
{
	int		i;
	int		j;
	void	*texture;

	i = -1;
	while (all->map.map[++i])
	{
		j = -1;
		while (all->map.map[i][++j])
		{
			if (all->map.map[i][j] == '1')
				texture = all->img.wall_tx;
			else if(all->map.map[i][j] == '0')
				texture = all->img.floor_tx;
			else if(ft_strchr(DIRS, all->map.map[i][j]))
				texture = all->img.floor_tx;
			else
				texture = all->img.space_tx;
			mlx_put_image_to_window(all->mlx, all->win, \
			texture, j * 16, i * 16);
		}
	}
	mlx_put_image_to_window(all->mlx, all->win, \
	all->img.player_tx, all->player.x / 64, all->player.y / 64);
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
		all.mlx = mlx_init();
		all.win = mlx_new_window(all.mlx, Win_x, Win_y, "cub3d");
		if (valid_identifiers(all.identifier) == 1
			&& ft_fprintf(2, "❌ Error : invalid identifier\n"))
			exit (1);
		music(&all);
		ft_textur_path(&all);
		init(&all);
		mlx_hook(all.win, 2, 0, event, &all);
		ray_casting(&all);
		draw_minimap(&all);
		mlx_hook(all.win, 17, 1L << 17, ft_close, &all);
		mlx_loop(all.mlx);
	}
	return (0);
}
