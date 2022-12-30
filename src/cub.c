/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:25:33 by arakhurs          #+#    #+#             */
/*   Updated: 2022/12/30 18:44:45 by arakhurs         ###   ########.fr       */
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

void	ft_map(t_all *all, t_map *map, const char *mpath)
{
	int		fd;
	char	*line;
	char	*str;

	str = NULL;
	if (ft_strncmp(".cub", (mpath + (ft_strlen(mpath) - 4)), 4) != 0)
		ft_error("❌ Map format is not *.cub");
	fd = open(mpath, O_RDONLY);
	if (fd == -1)
		ft_error("❌ Can't Open MAP 🗺");
	while (1)
	{
		line = get_next_line(fd);
		str = ft_strjoin(str, line);
		if (line == NULL)
			break ;
	}
	free(line);
	if (close(fd) == -1)
		ft_error("❌ Can't close Map File 🗺");
	ft_check_split(map, str);
	ft_free_array(&str);
	if (!(*(map->matrix)))
		ft_error("❌ Can't split❗️");
	ft_check_map(all, map);
}

int	main(int ac, char **av)
{
	t_all	all;

	if (ac == 2)
	{
		ft_map(&all, &all.map, av[1]);
		// sound_init(&all);
		// sound_play(&all, Sound_D1, 1);
		ft_win(&all);
		mlx_hook(all.win, 2, 0, ft_key_press, &all);
		//mlx_loop_hook(all.mlx, &loop_hook, &a);
		mlx_loop(all.mlx);
	}
	return 0;
}
