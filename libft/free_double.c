/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_double.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:38:44 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/15 19:35:34 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


int	free_double(char ***ptr)
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
