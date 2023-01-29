/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:06:10 by arakhurs          #+#    #+#             */
/*   Updated: 2023/01/29 12:29:29 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"
#include <math.h>

void	sound_play(t_all *g, int sound, t_bool loop)
{
	char	buffer[260];
	int		vol;
	char	*volstr;

	if (sound < 0 || sound >= Sound_Num || !g->resource.sounds[sound])
		return ;
	ft_strlcpy(buffer, "./play ", sizeof(buffer));
	if (loop)
		ft_strlcat(buffer, "-l ", sizeof(buffer));
	if (loop)
		vol = 50;
	else
		vol = 100;
	if (vol < 0)
		return ;
	ft_strlcat(buffer, " -v ", 260);
	volstr = ft_itoa(vol);
	if (!volstr)
		return ;
	ft_strlcat(buffer, volstr, 260);
	ft_strlcat(buffer, " ", 260);
	ft_strlcat(buffer, g->resource.sounds[sound], sizeof(buffer));
	ft_strlcat(buffer, " &", sizeof(buffer));
	system(buffer);
	free(volstr);
}

void	sound_stop(t_all *all, int sound)
{
	char	buffer[260];

	if (sound < 0 || sound >= Sound_Num || !all->resource.sounds[sound])
		return ;
	ft_strlcpy(buffer, "./stop ", sizeof(buffer));
	ft_strlcat(buffer, all->resource.sounds[sound], sizeof(buffer));
	ft_strlcat(buffer, " &", sizeof(buffer));
	system(buffer);
}

void	sound_init(t_all *all)
{
	char	**s;

	s = all->resource.sounds;
	s[Sound_None] = NULL;
	s[Sound_D1] = "./DOOM-1.mp3";
	s[Sound_I] = "./Smoke.mp3";
}
