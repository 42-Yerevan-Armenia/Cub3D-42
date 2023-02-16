/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_mappars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:43:23 by arakhurs          #+#    #+#             */
/*   Updated: 2023/02/16 16:51:00 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

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
	if (!get_identifier(identifier, "NO")
		|| !get_identifier(identifier, "SO")
		|| !get_identifier(identifier, "EA")
		|| !get_identifier(identifier, "WE")
		|| !get_identifier(identifier, "F")
		|| !get_identifier(identifier, "C"))
		return (1);
	return (0);
}

void	get_elems(char *line, char	**first, char **second)
{
	int		i;
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

int	ft_check_extens(const char *mpath, t_all *all)
{
	if (ft_strlen(mpath) < 5
		|| ft_strcmp(".cub", (char *)mpath + (ft_strlen(mpath) - 4)) != 0)
	{
		ft_error(all, "❌ Map format is not *.cub");
		return (1);
	}
	return (0);
}
