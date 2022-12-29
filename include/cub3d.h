/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:31:19 by vaghazar          #+#    #+#             */
/*   Updated: 2022/12/19 16:36:23 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../ft_fprintf/ft_printf.h"
#include <stdio.h>
#include <unistd.h>
#include <mlx.h>
#include "defines.h"
#include "struct.h"
#include <fcntl.h>
#include <errno.h>

# define CHECK(X) ({int __val = (X); (__val == -1 ? \
                    ({ft_fprintf(2, "Error: ("__FILE__" :%d) -- %s\n", \
                    __LINE__ , strerror(errno)); \
                    exit(-1); -1;}) : __val); })
// parsing

int     check_ext(char *str);
int		ft_fprintf(int fd, const char *from, ...);
char	*get_next_line(int fd);
