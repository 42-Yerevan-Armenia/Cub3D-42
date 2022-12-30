/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:54:42 by arakhurs          #+#    #+#             */
/*   Updated: 2022/12/30 18:53:26 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	ft_error(char *str)
{
	if (str && *str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
		exit(EXIT_FAILURE);
	}
}

void	ft_free_array(char **c)
{
	if (!c || !*c)
		return ;
	free(*c);
	*c = NULL;
}

size_t	ft_strnlen(const char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}

void	truncate_str(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	len--;
	while (len >= 0 && s[len] == ' ')
		s[len--] = 0;
}

char	*read_arg(char *s1, char *s2, char **ret)
{
	while (*s1 && *s2)
	{
		if (*s2 == ' ')
		{
			s2++;
			continue ;
		}
		if (*s1 != *s2)
			return (0);
		s2++;
		s1++;
	}
	if (*s1 == 0 && *s2 == ' ')
	{
		while (*s2 == ' ')
			s2++;
		truncate_str(s2);
		*ret = s2;
		return (s2);
	}
	return (0);
}