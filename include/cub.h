/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:11:58 by arakhurs          #+#    #+#             */
/*   Updated: 2022/12/29 19:42:55 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libft/libft.h"
# include "cub3d.h"
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
# define MAX_RESOURCE 128

# define ALL_CHARS	"_01NSEW"
# define IN_CHARS	"0NSEW"
# define DIRECTIONS	"NSEW"

enum			e_sound
{
	Sound_None,
	Sound_D1,
	Sound_Num
};

typedef int		t_bool;

typedef struct s_size
{
	int			width;
	int			height;
}				t_size;

typedef struct s_image
{
	t_size		size;
	size_t		bytes_per_pixel;
}				t_image;

typedef struct s_texset
{
	t_image		**imgs;
	int			imgcnt;
	int			i;
}				t_texset;

typedef struct s_resources
{
	t_texset	*texs[MAX_RESOURCE];
	char		*sounds[Sound_Num];
}				t_resources;

typedef struct s_map
{
	int			x;
	int			y;
	int			coin;
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
	t_resources	resource;
}				t_all;

//MAP 🗺
void	ft_fill_space(t_map *map);
void	ft_check_wall(t_map *map);
void	ft_check_map(t_map *map);
void	ft_check_split(t_map *map, char *str);
int		ft_check_char(char *map, char *symbol);



//UTILES 🛠
void	ft_error(char *str);
void	ft_free_array(char **c);
size_t	ft_strnlen(const char *str, char c);

//SOUNDS 🔊
void	sound_init(t_all *all);
void	sound_stop(t_all *all, int sound);
void	sound_play(t_all *g, int sound, t_bool loop);

char	*get_next_line(int fd);

#endif
