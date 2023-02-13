/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:54:42 by arakhurs          #+#    #+#             */
/*   Updated: 2023/02/13 15:36:48 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	ft_error(t_all *all, char *str)
{
	sound_stop(all, 0);
	sound_stop(all, 1);
	if (str && *str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
		exit(EXIT_FAILURE);
	}
}

int	ft_free_array(char **c)
{
	if (!c || !*c)
		return (1);
	free(*c);
	*c = NULL;
	return (1);
}

int	ft_free_double(char ***ptr)
{
	int	i;

	i = 0;
	if (*ptr == NULL)
		return (0);
	while ((*ptr) && ((*ptr))[i])
	{
		free(((*ptr))[i]);
		((*ptr))[i++] = NULL;
	}
	if (((*ptr)))
		free(((*ptr)));
	((*ptr)) = NULL;
	return (0);
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

void	music(t_all *all)
{
	sound_init(all);
	sound_play(all, Sound_I, 0);
	sleep(2);
	sound_play(all, Sound_D1, 1);
}
