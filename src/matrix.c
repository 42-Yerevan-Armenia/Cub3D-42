/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 19:35:40 by arakhurs          #+#    #+#             */
/*   Updated: 2023/01/16 21:09:34 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	get_matrix(t_all *all, const char	*mpath, int line_len)
{
	int		fd;
	char	*line;
	char	*ptr_for_free;
	int		i;
	int		flag;

	flag = 0;
	i = 0;
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
		}
		else if (*ptr_for_free == '\0' && i > 6)
		{
			if (flag != 2)
				flag = 1;
		}
		ft_free_array(&ptr_for_free);
		if (line == NULL)
			break ;
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

char	*get_identifier(char	**identifier, char	*idtf)
{
	int		i;

	i = 0;
	while (identifier[i] && identifier[i + 1])
	{
		if (ft_strcmp(identifier[i], idtf) == 0)
			return (identifier[i + 1]);
		i += 2;
	}
	return (0);
}

int	valid_identifiers(char	**identifier)
{
	int		i;

	if (!get_identifier(identifier, "NO")
		|| !get_identifier(identifier, "SO")
		|| !get_identifier(identifier, "EA")
		|| !get_identifier(identifier, "WE")
		|| !get_identifier(identifier, "F")
		|| !get_identifier(identifier, "C"))
		return (1);
	return (0);
}
