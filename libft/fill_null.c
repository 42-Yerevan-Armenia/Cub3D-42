/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_null.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:08 by vaghazar          #+#    #+#             */
/*   Updated: 2022/12/29 19:10:49 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fill_null(void ***ptr, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		(*ptr)[i++] = NULL;
	}
	return (0);
}
