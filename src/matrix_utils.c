/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 19:41:09 by arakhurs          #+#    #+#             */
/*   Updated: 2023/01/08 19:41:53 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	get_elems(char *line, char	**first, char **second)
{
	int		i;
	char	*res;
	char	*ptr_for_free;

	i = 0;
	while (line[i] && ft_strchr(SPACES, line[i]))
		i++;
	while (line[i] && !ft_strchr(SPACES, line[i]))
		i++;
	ptr_for_free = ft_substr(line, 0, i);
	*first = ft_strtrim(ptr_for_free, SPACES);
	ft_free_array(&ptr_for_free);
	ptr_for_free = ft_substr(line, i, ft_strlen(line));
	*second = ft_strtrim(ptr_for_free, SPACES);
	ft_free_array(&ptr_for_free);
}

void	set_identifers(t_all *all)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = all->matrix;
	while (tmp[i] && i < 6)
	{
		get_elems(tmp[i], &all->identifier[j], &all->identifier[j + 1]);
		j += 2;
		i++;
	}
}

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
			break ;
		ft_free_array(&line);
		count++;
	}
	CHECK(close(fd));
	return (count);
}
