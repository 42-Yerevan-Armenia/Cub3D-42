/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:53:23 by arakhurs          #+#    #+#             */
/*   Updated: 2022/12/30 19:07:36 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

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
			if (i == 6 && (map->matrix[i][j] != '1' || map->matrix[i][j] == '_') && j <= map->x - 1)
				ft_error("❌ The map not closed/surrounded by walls 🚧 ⬆️");
			else if ((map->matrix[i][j] != '1' && map->matrix[i][j - 1] == '_') && j <= map->x - 1)
				ft_error("❌ The map not closed/surrounded by walls 🚧 ⬇️");
			else if ((j == 0 && map->matrix[i][j] != '1') || (i == map->y - 1 && map->matrix[i][j] != '1' && j < map->x))
				ft_error("❌ The map not closed/surrounded by walls 🚧 ⬅️");
			else if ((map->matrix[i][j] && (map->matrix[i][j] != '1' && map->matrix[i][j + 1] == '_') \
				&& j <= map->x - 1) || (j == map->x - 1 && map->matrix[i][j] != '1'))
				ft_error("❌ The map not closed/surrounded by walls 🚧 ➡️");

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
			map->tmp = malloc(map->x + 1);
			strcpy(map->tmp, map->matrix[i]);
			j = 0;
			while (map->tmp[j])
				j++;
			while (j < map->x)
				map->tmp[j++] = '_';
			map->tmp[j] = '\0';
			free(map->matrix[i]);
			map->matrix[i] = map->tmp;
		}
		//printf("%s\n", map->matrix[i]);
		if (!ft_check_char(map->matrix[i], ALL_CHARS))
			ft_error("❌ No correct symbol in MAP 🗺");
		i++;
	}
}

int	ft_wall_path(t_map *map)
{
	int		i;
	char	*arg;

	i = 0;

	if ((!ft_strncmp(map->matrix[i], "NO", 2)) == 0)
		ft_error("❌ Not a Valid path 🛣  for NO ❗️");
	// if ((!ft_strncmp(map->matrix[i], "SO", 2)) == 0)
	// 	ft_error("❌ Not a Valid path 🛣  for SO ❗️");
	// if ((!ft_strncmp(map->matrix[i], "EA", 2)) == 0)
	// 	ft_error("❌ Not a Valid path 🛣  for EA ❗️");
	// if ((!ft_strncmp(map->matrix[i], "WE", 2)) == 0)
	// 	ft_error("❌ Not a Valid path 🛣  for WE ❗️");
	read_arg("NO", map->matrix[i], &arg);
	printf("%s\n", arg);
	return (0);
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
	ft_wall_path(map);
	ft_check_wall(map);
	//map->coin = 0;
	//ft_check_num(map->matrix, &(map->coin));	
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
