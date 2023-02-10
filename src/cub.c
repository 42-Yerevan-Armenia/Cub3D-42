/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:25:33 by arakhurs          #+#    #+#             */
/*   Updated: 2023/02/09 20:38:34 by arakhurs         ###   ########.fr       */
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
/*
int		map_get(t_map *map, int x, int y)
{
	int pos;

	pos = y * map->x + x;
	if (x < 0 || y < 0 || x >= map->x || y >= map->y)
		return (0);
	return (map->data[pos] == 1);
}

void	set_pixel(t_data *data, int x, int y, int color)
{
	*(unsigned int*)(data->addr +
		(y * data->line_length + x * data->bits_per_pixel)) = color;
}

int		get_pixel(t_data *data, int x, int y)
{
	return (*(int*)(data->addr + (y * data->line_length + x
		* (data->bits_per_pixel))));
}

int		blend_colors(int o, int n)
{
	float	a;
	int		r;
	int		g;
	int		b;

	a = 1 - ((n >> 24) & 0xFF) / 255.0f;
	if (a == 1)
		return (n);
	r = (int)(((o & 0xff0000) >> 16) * (1 - a) + ((n & 0xff0000) >> 16) * a);
	g = (int)(((o & 0xff00) >> 8) * (1 - a) + ((n & 0xff00) >> 8) * a);
	b = (int)((o & 0xff) * (1 - a) + (n & 0xff) * a);
	return (0 << 24 | r << 16 | g << 8 | b);
}

void	rect(t_data *data, t_map *map, int color)
{
	int i;
	int j;
	int b;

	i = fmax(map->x, 0);
	while (i < map->x + map->width && i < 12)
	{
		j = fmax(map->y, 0);
		while (j < map->y + map->height && j <12)
		{
			b = get_pixel(data, i, j);
			set_pixel(data, i, j, blend_colors(b, color));
			++j;
		}
		++i;
	}
}

void	draw_rects(t_map *map, t_all *all)
{
	int	i;

	if (map_get(map, map->v_x + (int)(map->s_x), map->v_y 
		+ (int)(map->s_y)))
		rect(&all->win_img_data, map, 0xA07BADCD);
	i = 0;
	while (map->map && map->m_i != -999)
	{
	printf("❌%d + %f = %d\n", map->v_x, map->s_x, map->m_i);
		if ((map->v_x + (int)(map->s_x)) == map->m_i &&
			(map->v_y + (int)(map->s_y)) == map->m_j)
			rect(&all->win_img_data, map, 0xC0D34141);
		i++;
	}
	
}*/

void	draw_minimap(t_all *all)
{

	all->map.s_x -= (all->map.s_x - all->player.x) * 0.17;
	all->map.s_y -= (all->map.s_y - all->player.y) * 0.17;
	all->map.width = 12;
	all->map.height = 12;
	all->map.p_x = -fabs(fmod(all->map.s_x, 1)) * all->map.width;
	all->map.v_x = -9;
	while (++all->map.v_x)
	{
		all->map.v_y = -6;
		all->map.p_y = -fabs(fmod(all->map.s_y, 1)) * all->map.height;
		while (all->map.v_y <= 7)
		{
			//draw_rects(&all->map, all);
			all->map.p_y += all->map.height + 1;
			all->map.v_y++;
		}
		all->map.p_x += all->map.width + 1;
	}
	// draw_minidot(all);
}




/*
void	minimap(t_list *map, t_all *all)
{
	double	y;
	double	x;

	if (all->map.minimap)
		mlx_destroy_image(all->mlx, all->map.minimap);
	all->map.minimap = mlx_new_image(all->mlx, 1000 / 5, 600 / 5);
	y = 0;
	printf("❌\n");
	while (all->map.y > 11 && all->player.y > y + 6 && all->map.y > y + 10)
	{
		printf("❌ %s\n", map->content);
		map = map->next;
		y++;
	}
	if (all->map.x < 11 || all->player.x <= 4)
		x = 0;
	else if (all->map.x - all->player.x <= 6)
		x = all->map.x - 10;
	else
		x = all->player.x - 4;
	//ft_sub_minimap(map, all, x);
	mlx_put_image_to_window(all->mlx, all->win, all->map.minimap, 0, 0);
}*/

#define MINIMAP_W 200
#define MINIMAP_H 200
#define MINIMAP_X 10
#define MINIMAP_Y 10
#define WALL_COLOR 0xFF0000
#define FLOOR_COLOR 0x00FF00
#define PLAYER_COLOR 0x0000FF
/*
void	draw_minimap(void *mlx, void *win, t_player player, t_all *all)
{

	int		i;
	int		j;
	double	scale_x;
	double	scale_y;
	int		player_x;
	int		player_y;

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
				mlx_pixel_put(mlx, win, j, i, 0xFF0000);
			else
				mlx_pixel_put(mlx, win, j, i, 0xFFD700);
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
	//mlx_clear_window(all->mlx, all->win);
	for (y = 0; y < MINIMAP_H; y++)
	{
		for (x = 0; x < MINIMAP_W; x++)
		{
			if (map[y][x] == '1')
				mlx_pixel_put(mlx, win, x + MINIMAP_X, y + MINIMAP_Y, WALL_COLOR);
			else
				mlx_pixel_put(mlx, win, x + MINIMAP_X, y + MINIMAP_Y, FLOOR_COLOR);
		}
	}
	mlx_pixel_put(mlx, win, player.x + MINIMAP_X, player.y + MINIMAP_Y, PLAYER_COLOR);
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
		all.mlx = mlx_init();
		all.win = mlx_new_window(all.mlx, Win_x, Win_y, "cub3d");
		if (valid_identifiers(all.identifier) == 1
			&& ft_fprintf(2, "❌ Error : invalid identifier\n"))
			exit (1);
		sound_init(&all);
		sound_play(&all, Sound_I, 0);
		sleep(2);
		sound_play(&all, Sound_D1, 1);
		ft_textur_path(&all);
		init(&all);
		mlx_hook(all.win, 2, 0, event, &all);
		ray_casting(&all);
		mlx_hook(all.win, 17, 1L << 17, ft_close, &all);
		//draw_minimap(all.mlx, all.win, all.player, &all);
		draw_minimap(&all);
		mlx_loop(all.mlx);
		//signal(SIGINT, ft_destroy(&all));
	}
	return 0;
}
