/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:46:05 by arakhurs          #+#    #+#             */
/*   Updated: 2023/02/16 18:23:20 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static int	ft_count_lines(t_all *all, const char *mpath)
{
	int		count;
	char	*line;
	int		fd;

	count = 0;
	fd = open(mpath, O_RDONLY);
	if (fd == -1 && ft_perror("❌ Open : "))
		exit(1);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		ft_free_array(&line);
		count++;
	}
	if (close(fd) == -1 && ft_perror("❌ Close : "))
		exit(1);
	return (count);
}

static void	split_matrix(t_all *all, int flag, char	*ptr_for_free, int i)
{
	while (1)
	{
		all->map.line = get_next_line(all->map.fd);
		ptr_for_free = ft_strtrim(all->map.line, SPACES);
		if (all->map.line == NULL && flag == 2)
			ft_error(all, "❌ Can't split❗️");
		else if (all->map.line == NULL || *ptr_for_free != '\0')
		{
			if (flag == 1)
				flag = 2;
			if (all->map.line != NULL)
				all->matrix[i++] = ft_strtrim(all->map.line, "\n");
			else
				all->matrix[i++] = NULL;
		}
		else if (*ptr_for_free == '\0' && i > 6)
		{
			if (flag != 2)
				flag = 1;
		}
		ft_free_array(&ptr_for_free);
		if (all->map.line == NULL)
			break ;
		free(all->map.line);
	}
}

static void	get_matrix(t_all *all, const char	*mpath, int line_len)
{
	char	*ptr_for_free;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	ptr_for_free = NULL;
	all->map.line = NULL;
	all->map.fd = (open(mpath, O_RDONLY));
	if (all->map.fd == -1 && ft_perror("❌ open : "))
		exit(1);
	all->matrix = malloc(sizeof(char *) * (line_len + 1));
	split_matrix(all, flag, ptr_for_free, i);
	if (close(all->map.fd) == -1 && ft_perror("❌ close : "))
		exit(1);
}

void	ft_matrix(t_all *all, const char *mpath)
{
	int		line_len;

	if (ft_strlen(mpath) < 5
		|| ft_strcmp(".cub", (char *)mpath + (ft_strlen(mpath) - 4)) != 0)
		ft_error(all, "❌ Map format is not *.cub");
	line_len = ft_count_lines(all, mpath);
	if (line_len == 0)
		ft_error(all, "❌ Empty file 🗿");
	else if (line_len < 6)
		ft_error(all, "❌ Empty matrix 🎨");
	get_matrix(all, mpath, line_len);
	all->map.map = (all->matrix) + 6;
	ft_check_map(&all->map, all);
	all->map.s_x = all->player.x;
	all->map.s_y = all->player.y;
}
