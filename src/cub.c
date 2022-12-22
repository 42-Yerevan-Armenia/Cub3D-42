/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:25:33 by arakhurs          #+#    #+#             */
/*   Updated: 2022/12/22 22:01:43 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	ft_error(char *str)
{
	if (str && *str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
		exit(EXIT_FAILURE);
	}
}

void	ft_free_array(char **c)
{
	if (!c || !*c)
		return ;
	free(*c);
	*c = NULL;
}

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

void	ft_check_wall(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->y)
	{
		j = 0;
		while (j < map->x)
		{
			if (i == 0 && (map->matrix[i][j] != '1'))
				ft_error("❌ The map not closed/surrounded by walls 🚧 1");
			else if (j == 0 && map->matrix[i][j] != '1')
				ft_error("❌ The map not closed/surrounded by walls 🚧 2");
			else if (i == map->y - 1 && map->matrix[i][j] != '1')
				ft_error("❌ The map not closed/surrounded by walls 🚧 3");
			else if ((j == map->x - 1 && map->matrix[i][j] != '1') || \
				map->matrix[i][map->x] != '\0')
				ft_error("❌ The map not closed/surrounded by walls 🚧 4");
			j++;
		}
		i++;
	}
}

void	ft_check_map(t_map *map)
{
	map->y = 0;
	while (&(map->matrix[map->y][0]) != NULL)
		map->y++;
	map->x = 0;
	while (map->matrix[0][map->x] != '\0')
		map->x++;
	if (map->y <= 0 || map->x <= 0)
		ft_error("❌ Not a Valid Map 🗺❗️");
	ft_check_wall(map);
	//map->coin = 0;
	//ft_check_num(map->matrix, &(map->coin));	
}

void	ft_till_split(t_map *map, char *str)
{
	int	i;
	int	j;

	i = 0;
	if (ft_isalpha(str[i]))
		map->matrix = ft_split(str, '\n');
	while (i < 7)
	{
		if (!ft_isalpha(map->matrix[i][0]))
		{
			j = 0;
			while (map->matrix[i][j] != '\0')
			{
				if (map->matrix[i][j] == '\n' && map->matrix[i + 1][j] == '\n')
				{
					ft_error("1❌ Can't split❗️");
					exit(0);
				}
				j++;
			}
			i++;
		}
		i++;
	}
}

// void	ft_till_split(t_map *map, char *str)
// {
// 	int	i;
// 	int	j;

// 	map->matrix = ft_split(str, '\n');
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		j = 0;
// 		while (str[i] != '\n')
// 		{
// 			if (!ft_isalpha(map->matrix[j][0]))
// 			{
// 				printf("%c\n", str[i]);
// 				while (str[i] != '\0')
// 				{
// 					if (str[i] == '\n' && str[i + 1] == '\n')
// 					{
// 						ft_error("1❌ Can't split❗️");
// 						exit(0);
// 					}
// 					i++;
// 				}
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	ft_check_split(t_map *map, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n' && str[i + 1] == '\n')
		{
			ft_error("❌ Can't split❗️");
			exit(0);
		}
		i++;
	}
	map->matrix = ft_split(str, '\n');
}

void	ft_map(t_map *map, const char *mpath)
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
		if (*line == (char) NULL)
			break ;
	}
	free(line);
	if (close(fd) == -1)
		ft_error("❌ Can't close Map File 🗺");
	ft_till_split(map, str);
	ft_check_split(map, str);
	ft_free_array(&str);
	if (!(*(map->matrix)))
		ft_error("❌ Can't split❗️");
	ft_check_map(map);
}

int	main(int ac, char **av)
{
	t_all	all;

	if (ac == 2)
	{
		ft_map(&all.map, av[1]);
		sound_init(&all);
		sound_play(&all, Sound_D1, 1);
		ft_win(&all);
		mlx_hook(all.win, 2, 0, ft_key_press, &all);
		//mlx_loop_hook(all.mlx, &loop_hook, &a);
		mlx_loop(all.mlx);
	}
	return 0;
}
