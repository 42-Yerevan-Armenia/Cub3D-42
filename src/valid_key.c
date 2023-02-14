/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:58:19 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/14 17:58:33 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	valid_key(int key)
{
	if (key == KEY_W || key == KEY_S || key == KEY_A
		|| key == KEY_D || key == KEY_ARROW_LEFT
		|| key == KEY_ARROW_RIGHT || key == KEY_ESC)
		return (1);
	return (0);
}
