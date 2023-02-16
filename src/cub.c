/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:25:33 by arakhurs          #+#    #+#             */
/*   Updated: 2023/02/16 20:18:03 by arakhurs         ###   ########.fr       */
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
	return (0);
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
			else if (all->map.map[i][j] == '0')
				texture = all->img.floor_tx;
			else if (ft_strchr(DIRS, all->map.map[i][j]))
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

void	ft_win(t_all *all)
{
	all->mlx = mlx_init();
	if (all->mlx == NULL)
		ft_error(all, "❌ Can't do it 🤣");
	all->win = mlx_new_window(all->mlx, Win_x, Win_y, "Title");
	if (all->win == NULL)
		ft_error(all, "❌ Can't Creat Window 📺");
	mlx_hook(all->win, 17, 0, ft_destroy, all);
	mlx_hook(all->win, 2, 0, event, all);
}

int	main(int ac, char **av)
{
	t_all	all;

	if (ac == 2)
	{
		init(&all);
		valid_args(&all, av[1]);
		set_identifers(&all);
		if (valid_identifiers(all.identifier) == 1
			&& ft_fprintf(2, "❌ Error : invalid identifier\n"))
			exit (1);
		ft_matrix(&all);
		ft_win(&all);
		music(&all);
		ft_textur_path(&all);
		if (init_img(&all) == 1)
			exit (1);
		ray_casting(&all);
		if (all.map.flag_map && all.map.flag_size)
			draw_minimap(&all);
		mlx_loop(all.mlx);
	}
	return (0);
}
