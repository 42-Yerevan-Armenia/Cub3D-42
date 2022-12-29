/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 13:44:00 by vaghazar          #+#    #+#             */
/*   Updated: 2022/12/19 15:24:02 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

char	*ft_check_base(char c, unsigned long *nbr, unsigned long *num);
int		ft_printf_type(const char *from, int *tmp, va_list ap, int fd);
int		ft_fprintf(int fd, const char *from, ...);
void	ft_putchar(char c, int *count, int fd);
void	ft_putnbr_base(unsigned long nbr, int *count, char c, int fd);
void	ft_putnbr(long nb, int *count, char c, int fd);
int		ft_putstr(char *str, int *count, int fd);

#endif
