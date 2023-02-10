/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:53:23 by arakhurs          #+#    #+#             */
/*   Updated: 2023/02/09 15:56:17 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

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
			while (map->map[i][j] == '_')
				j++;
			if (map->map[i][j] && ft_strchr(IN_CHARS, map->map[i][j]) && \
				(i == 0 || j == 0 || i == (map->y - 1) || j == (map->x - 1) || \
				map->map[i - 1][j] == '_' || map->map[i + 1][j] == '_' || \
				map->map[i][j - 1] == '_' || map->map[i][j + 1] == '_'))
				ft_error("❌ The map not closed/surrounded by walls 🚧");
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

	i = 0;
	while (i < map->y)
	{
		j = 0;
		min = ft_strlen(map->map[i]);
		while (map->map[i][j])
		{
			if (map->map[i][j] == ' ')
				map->map[i][j] = '_';
			j++;
		}
		if (map->map[i][j] == '\t')
			ft_error("❌ No correct symbol in MAP 🗺");
		if (min < map->x)
		{
			map->tmp = malloc(map->x + 1);
			strcpy(map->tmp, map->map[i]);
			j = 0;
			while (map->tmp[j])
				j++;
			while (j < map->x)
				map->tmp[j++] = '_';
			map->tmp[j] = '\0';
			free(map->map[i]);
			map->map[i] = map->tmp;
		}
		i++;
	}
}

void	ft_check_num(char **n, t_all *all)
{
	int	i;
	int	j;
	int	e_p[1];

	e_p[0] = 0;
	i = -1;
	while (n[++i])
	{
		j = -1;
		while (n[i][++j])
		{
			if (!ft_check_char(n[i], ALL_CHARS))
				ft_error("❌ No correct symbol in MAP 🗺");
			if (ft_strchr(DIRS, n[i][j]))
			{
				all->player.x = (j * Field) + (Field / 2);
				all->player.y = (i * Field) + (Field / 2);
				all->map.s_x = all->player.x;
				all->map.s_y = all->player.y;
				all->player.angle = pov(n[i][j]);
				n[i][j] = '0';
				all->map.m_i = i;
				all->map.m_j = j;
				e_p[0]++;
			}
		}
	}
	if ((e_p[0] != 1))
		ft_error("❌Map symbol count Error❗️");
}

void	ft_check_map(t_map *map, t_all *all)
{
	int	min;
	int	l;

	map->y = 0;
	map->max = ft_strlen(map->map[0]);
	l = map->y;
	while (&(map->map[map->y][0]) != NULL)
	{	
		min = ft_strlen(map->map[map->y]);
		if (min > map->max && map->y)
		{
			map->max = min;
			l = map->y;
		}
		map->y++;
	}
	map->x = 0;
	while (map->map[l][map->x] != '\0')
		map->x++;
	if (map->y <= 0 || map->x <= 0)
		ft_error("❌ Not a Valid Map 🗺❗️");
	ft_fill_space(map);
	ft_check_wall(map);
	ft_check_num(map->map, all);
}
