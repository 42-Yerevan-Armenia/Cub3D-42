/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:36:59 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/15 21:35:25 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *src, unsigned int start, size_t len)
{
	char	*ptr;
	int		i;
	size_t	s_len;

	s_len = ft_strlen(src + start);
	if (start >= (unsigned int)ft_strlen(src))
	{
		return (ft_strdup(""));
	}
	if (s_len < len)
		len = s_len;
	ptr = (char *) malloc(len + 1);
	if (ptr == 0)
		return (0);
	i = 0;
	while (src[start] && len--)
		ptr[i++] = src[start++];
	ptr[i] = '\0';
	return (ptr);
}
