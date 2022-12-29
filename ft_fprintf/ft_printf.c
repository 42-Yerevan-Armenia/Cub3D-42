/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 13:27:59 by vaghazar          #+#    #+#             */
/*   Updated: 2022/12/19 15:49:03 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_fprintf(int fd, const char *from, ...)
{
	va_list	ap;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(ap, from);
	while (from[i] != 0)
	{
		if (from[i] == '%' && ++i)
			count += ft_printf_type(from, &i, ap, fd);
		if (from[i] != 0 && from[i] != '%')
			ft_putchar(from[i++], &count, fd);
	}
	va_end(ap);
	return (count);
}
