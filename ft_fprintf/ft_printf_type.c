/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 19:56:58 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/15 11:39:41 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_type(const char *from, int *tmp, va_list ap, int fd)
{
	int	i;
	int	count;

	count = 0;
	i = *tmp;
	if (from[i] == 'c' && ++i)
		ft_putchar(va_arg(ap, int), &count, fd);
	else if (from[i] == 's' && ++i)
		ft_putstr(va_arg(ap, char *), &count, fd);
	else if ((from[i] == 'p' && ft_putstr("0x", &count, fd))
		|| from[i] == 'x' || from[i] == 'X')
		ft_putnbr_base(va_arg(ap, unsigned long), &count, from[i++], fd);
	else if ((from[i] == 'd' || from[i] == 'i' || from[i] == 'u'))
		ft_putnbr(va_arg(ap, int), &count, from[i++], fd);
	else if (from[i] == '%')
		ft_putchar(from[i++], &count, fd);
	*tmp = i;
	return (count);
}
