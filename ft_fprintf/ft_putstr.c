/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:31:14 by vaghazar          #+#    #+#             */
/*   Updated: 2022/12/19 15:24:23 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str, int *count, int fd)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_putstr("(null)", count, fd);
		return (0);
	}
	while (str[i] != '\0')
	{
		ft_putchar(str[i], count, fd);
		i++;
	}
	return (i);
}
