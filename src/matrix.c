/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:46:05 by arakhurs          #+#    #+#             */
/*   Updated: 2023/02/13 15:21:16 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static int	ft_count_lines(const char *mpath)
{
	int		count;
	char	*line;
	int		fd;

	count = 0;
	fd = open(mpath, O_RDONLY);
	CHECK(fd);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		ft_free_array(&line);
		count++;
	}
	CHECK(close(fd));
	return (count);
}

static void	split_matrix(t_all *all, char *line, int flag, \
	char	*ptr_for_free, int i)
{
	while (1)
	{
		line = get_next_line(all->map.fd);
		ptr_for_free = ft_strtrim(line, SPACES);
		if (line == NULL && flag == 2)
			ft_error(all, "❌ Can't split❗️");
		else if (line == NULL || *ptr_for_free != '\0')
		{
			if (flag == 1)
				flag = 2;
			if (line != NULL)
				all->matrix[i++] = ft_strtrim(line, "\n");
			else
				all->matrix[i++] = NULL;
		}
		else if (*ptr_for_free == '\0' && i > 6)
		{
			if (flag != 2)
				flag = 1;
		}
		ft_free_array(&ptr_for_free);
		if (line == NULL)
			break ;
		free(line);
	}
}

static void	get_matrix(t_all *all, const char	*mpath, int line_len)
{
	char	*line;
	char	*ptr_for_free;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	all->map.fd = (open(mpath, O_RDONLY));
	CHECK(all->map.fd);
	all->matrix = malloc(sizeof(char *) * (line_len + 1));
	split_matrix(all, line, flag, ptr_for_free, i);
	CHECK(close(all->map.fd));
}

void	ft_matrix(t_all *all, const char *mpath)
{
	int		line_len;
	int		i;

	if (ft_strlen(mpath) < 5
		|| ft_strcmp(".cub", (char *)mpath + (ft_strlen(mpath) - 4)) != 0)
		ft_error(all, "❌ Map format is not *.cub");
	line_len = ft_count_lines(mpath);
	get_matrix(all, mpath, line_len);
	all->map.map = (all->matrix) + 6;
	i = 0;
	ft_check_map(&all->map, all);
	all->map.s_x = all->player.x;
	all->map.s_y = all->player.y;
}
