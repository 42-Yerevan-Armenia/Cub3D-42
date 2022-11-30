/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:11:58 by arakhurs          #+#    #+#             */
/*   Updated: 2022/11/14 16:11:59 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <mlx.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WALL "./Texture/wall.xpm"
# define PLAYER "./Texture/exit.xpm"
# define DOOR "./Texture/door.xpm"

typedef struct s_map
{
	char		**matrix;
}				t_map;

typedef struct s_img
{
	void		*img;
}				t_img;

typedef struct s_player
{
	int			x;
	int			y;
}				t_player;

typedef struct s_all
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_img		img;
	t_player	player;
}				t_all;

#endif
