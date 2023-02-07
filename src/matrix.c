/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:46:05 by arakhurs          #+#    #+#             */
/*   Updated: 2023/02/07 12:52:42 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	ft_count_lines(const char *mpath)
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
			break;
		ft_free_array(&line);
		count++;

	}
	CHECK(close(fd));
	return (count);
}

void	get_matrix(t_all *all, const char	*mpath, int line_len)
{
	int		fd;
	char	*line;
	char	*ptr_for_free;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	fd = (open(mpath, O_RDONLY));
	CHECK(fd);
	all->matrix = malloc(sizeof(char *) * (line_len + 1));
	while (1)
	{
		line = get_next_line(fd);
		ptr_for_free = ft_strtrim(line, SPACES);
		if (line == NULL && flag == 2)
			ft_error("❌ Can't split❗️");
		else if (line == NULL || *ptr_for_free != '\0')
		{
			if (flag == 1)
				flag = 2;
			if (line != NULL)
				all->matrix[i++] = ft_strtrim(line, "\n");
			else
				all->matrix[i++] = NULL;
            // free(line); -> else	all->matrix[i++] = NULL;
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
        //all->matrix[i] = NULL; -> free(line);
	}
	CHECK(close(fd));
}

void	ft_matrix(t_all *all, const char *mpath)
{
	int		line_len;
	int		i;

	if (ft_strlen(mpath) < 5
		|| ft_strcmp(".cub", (char *)mpath + (ft_strlen(mpath) - 4)) != 0)
		ft_error("❌ Map format is not *.cub");
	line_len = ft_count_lines(mpath);
	get_matrix(all, mpath, line_len);
	all->map.map = (all->matrix) + 6;
	i = 0;
	// while (all->map.map[i])
	// 	printf("%s\n", all->map.map[i++]);
	ft_check_map(&all->map, all);
}
