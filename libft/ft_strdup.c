/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:33:50 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/15 19:36:16 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*ptr;

	i = 0;
	while (src && src[i])
		i++;
	ptr = malloc(i + 1);
	if (!ptr && !ft_perror("cub : "))
		return (0);
	i = 0;
	while (src && src[i])
	{
		ptr[i] = src[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
