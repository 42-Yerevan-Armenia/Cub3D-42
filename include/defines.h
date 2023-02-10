/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:05:58 by vaghazar          #+#    #+#             */
/*   Updated: 2023/02/07 20:12:13 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

#include "cub.h"

# define EXTENSION ".cub"
# define SPACES " \n\t\v\f\r"
# define PI 3.14159265359

# define ALL_CHARS	"_01NSEW"
# define IN_CHARS	"0NSEW"
# define DIRS		"NSEW"

# define HORIZ	1
# define VERT	2

# define START_LEFT	1
# define START_RIGHT 2

# define CHECK(X) ({int __val = (X); (__val == -1 ? \
                    ({ft_fprintf(2, "Error: ("__FILE__" :%d) -- %s\n", \
                    __LINE__ , strerror(errno)); \
                    exit(-1); -1;}) : __val); })

#endif
