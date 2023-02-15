/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:25:33 by arakhurs          #+#    #+#             */
/*   Updated: 2023/02/14 18:07:00 by vaghazar         ###   ########.fr       */
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

void	ft_win(t_all *all)
{
	all->mlx = mlx_init();
	if (all->mlx == NULL)
		ft_error(all, "❌ Can't do it 🤣");
	all->win = mlx_new_window(all->mlx, Win_x, Win_y, "Title");
	if (all->win == NULL)
		ft_error(all, "❌ Can't Creat Window 📺");
	all->img.img = mlx_new_image(all->mlx, Win_x, Win_y);
	mlx_hook(all->win, 17, 0, ft_destroy, all);
}

#define M_W 200
#define M_H 200

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
	// mlx_put_image_to_window(all->mlx, all->win, \
	// all->img.player_tx, all->player.x / 64, all->player.y / 64);
	mlx_put_image_to_window(all->mlx, all->win, \
	all->img.player_tx, all->player.x / 64, all->player.y / 64);
}

// void	draw_minimap(t_all *all)
// {
// 	(void)all;
// }

void	draw_minimaps(void *mlx, void *win, t_player player, t_all *all)
{
	(void)mlx;
	(void)win;
	(void)player;
	(void)all;
}

/*
void	draw_minimaps(void *mlx, void *win, t_player player, t_all *all)
{
	int		i;
	int		j;
	double	scale_x;
	double	scale_y;
	int		player_x;
	int		player_y;
	void	*texture;
	scale_x = MINIMAP_W / 64;
	scale_y = MINIMAP_H / 64;
	player_x = player.x * scale_x + all->map.x;
	player_y = player.y * scale_y + all->map.y;
	i = all->map.y;
	while (i < all->map.y + MINIMAP_H)
	{
		j = all->map.x;
		while (j < all->map.x + MINIMAP_W)
		{
			if (j >= player_x - 2 && j <= player_x + 2 &&
				i >= player_y - 2 && i <= player_y + 2)
				my_mlx_pixel_put(&all->win_img_data, j, i, 0xFF0000);
				// mlx_pixel_put(mlx, win, j, i, 0xFF0000);
			else
				my_mlx_pixel_put(&all->win_img_data, j, i, 0xFFD700);
				// mlx_pixel_put(mlx, win, j, i, 0xFFD700);
			j++;
		}
		i++;
	}
	int		x;
	int		y;
	char	**map;
	map = (char **)malloc(sizeof(char *) * MINIMAP_H);
	for (int i = 0; i < MINIMAP_H; i++)
	{
		map[i] = (char *)malloc(sizeof(char) * MINIMAP_W);
		for (int j = 0; j < MINIMAP_W; j++)
		{
			if (i % 10 == 0 || j % 10 == 0)
				map[i][j] = '1';
			else
				map[i][j] = '0';
		}
	}
	for (y = 0; y < MINIMAP_H; y++)
	{
		for (x = 0; x < MINIMAP_W; x++)
		{
			if (map[y][x] == '1')
				texture = all->img.wall_tx;
			else
				texture = all->img.floor_tx;
			mlx_put_image_to_window(all->mlx, all->win, \
			texture, j * 16, i * 16);
		}
	}
	mlx_put_image_to_window(all->mlx, all->win, \
	all->img.player_tx, all->player.x / 64, all->player.y / 64);
}
*/

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
		ft_win(&all);
		if (valid_identifiers(all.identifier) == 1
			&& ft_fprintf(2, "❌ Error : invalid identifier\n"))
			exit (1);
		//music(&all);
		ft_textur_path(&all);
		init(&all);
		mlx_hook(all.win, 2, 0, event, &all);
		ray_casting(&all);
		draw_minimap(&all);
		draw_minimaps(all.mlx, all.win, all.player, &all);
		mlx_loop(all.mlx);
	}
	return (0);
}

// int main()
// {
// 	printf("cos = %lf\n", cos(d_to_rdn(179)));
// 	printf("sin = %lf\n", sin(d_to_rdn(180)));
// }