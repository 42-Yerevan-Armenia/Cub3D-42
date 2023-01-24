/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:09:10 by arakhurs          #+#    #+#             */
/*   Updated: 2023/01/20 19:24:31 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	ft_key_press(int keycode, t_all *all)
{
	char	c;

	if (keycode == 53)
		ft_destroy(all);
	if (keycode == 13)
		ft_move_up(all);
	if (keycode == 0)
		ft_move_left(all);
	if (keycode == 1)
		ft_move_down(all);
	if (keycode == 2)
		ft_move_right(all);
	if (keycode == 123)
		ft_view_left(all);
	if (keycode == 124)
		ft_view_right(all);
	return (0);
}