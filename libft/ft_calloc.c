/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:17:49 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/15 21:34:09 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;

	ptr = (char *) malloc(size * nmemb);
	if (ptr == 0)
		return (0);
	ft_bzero(ptr, (nmemb * size));
	return (ptr);
}
