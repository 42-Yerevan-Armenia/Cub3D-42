/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:25:33 by arakhurs          #+#    #+#             */
/*   Updated: 2022/12/28 21:38:05 by arakhurs         ###   ########.fr       */
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

	i = 6;
	while (i < map->y)
	{
		j = 0;
		while (j < map->x)
		{
			while (map->matrix[i][j] == '_')
				j++;
			printf("\nline = %d max=%d\n", i, map->y);
			printf("rowe = %d max=%d\n", j, map->x);
			printf("[%c]\n", map->matrix[i][j]);
			if (i == 6 && (map->matrix[i][j] != '1'))
				ft_error("❌ The map not closed/surrounded by walls 🚧 1");
			else if (j == 0 && map->matrix[i][j] != '1')
				ft_error("❌ The map not closed/surrounded by walls 🚧 2");
			else if ((map->matrix[i][j] != '1' && map->matrix[i][j - 1] == '_') && j <= map->x - 1)
				ft_error("❌ The map not closed/surrounded by walls 🚧 _1");
			else if (map->matrix[i][j] && (map->matrix[i][j] != '1' && map->matrix[i][j + 1] == '_') && j <= map->x - 1)
				ft_error("❌ The map not closed/surrounded by walls 🚧 1_");
			else if (j == map->x - 1 && map->matrix[i][j] != '1')
				ft_error("❌ The map not closed/surrounded by walls 🚧 4");
			else if (i == map->y - 1 && map->matrix[i][j] != '1' && j < map->x)
				ft_error("❌ The map not closed/surrounded by walls 🚧 3");
			/*if (map->matrix[i][j] && ft_strchr(IN_CHARS, map->matrix[i][j]) && \
				(i == 6 || j == 0 || i == (map->y - 1) || j == (map->x - 1) || \
				map->matrix[i - 1][j] == '_' || map->matrix[i + 1][j] == '_' || \
				map->matrix[i][j - 1] == '_' || map->matrix[i][j + 1] == '_'))
				ft_error("❌ The map not closed/surrounded by walls 🚧 _");*/
			j++;
		}
		i++;
	}	
}

int	ft_check_char(char *map, char *symbol)
{
	int	i;

	if (!map || !symbol)
		return (0);
	i = -1;
	while (map[++i])
		if (!ft_strchr(symbol, map[i]))
			return (0);
	return (1);
}

void	ft_fill_space(t_map *map)
{
	int		i;
	int		j;
	int		min;
	char	*tmp;

	i = 6;
	while (i < map->y)
	{
		j = 0;
		min = ft_strlen(map->matrix[i]);
		while (map->matrix[i][j])
		{
			if (map->matrix[i][j] == ' ' || map->matrix[i][j] == '\t')
				map->matrix[i][j] = '_';
			j++;
		}
		if (min < map->x)
		{
			tmp = malloc(map->x + 1);
			strcpy(tmp, map->matrix[i]);
			j = 0;
			while (tmp[j])
				j++;
			while (j < map->x)
				tmp[j++] = '_';
			tmp[j] = '\0';
			free(map->matrix[i]);
			map->matrix[i] = tmp;
		}
		printf("%s\n", map->matrix[i]);
		if (!ft_check_char(map->matrix[i], ALL_CHARS))
			ft_error("❌ No correct symbol in MAP 🗺");
		i++;
	}
}

void	ft_check_map(t_map *map)
{
	int	max;
	int	min;
	int	l;

	map->y = 6;
	max = ft_strlen(map->matrix[6]);
	l = map->y;
	while (&(map->matrix[map->y][0]) != NULL)
	{	
		min = ft_strlen(map->matrix[map->y]);
		if (min > max && map->y)
		{
			max = min;
			l = map->y;
		}
		map->y++;
	}
	map->x = 0;
	while (map->matrix[l][map->x] != '\0')
		map->x++;
	if (map->y <= 0 || map->x <= 0)
		ft_error("❌ Not a Valid Map 🗺❗️");
	ft_fill_space(map);
	ft_check_wall(map);
	//map->coin = 0;
	//ft_check_num(map->matrix, &(map->coin));	
}

size_t	ft_strnlen(const char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}

void	ft_check_split(t_map *map, char *str)
{
	int	i;
	int	l;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n' && ft_isdigit(str[i + 1]))
		{	
			l = ft_strnlen(&str[i + 1], '\n');
			if (str[i + l + 1] == '\n' && str[i + l + 2] == '\n')
			{
				ft_error("❌ Can't split map❗️");
				exit(0);
			}
			i++;
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
