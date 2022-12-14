/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:11:58 by arakhurs          #+#    #+#             */
/*   Updated: 2023/01/08 19:44:22 by arakhurs         ###   ########.fr       */
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
# include <math.h>


# define PLAYER "./Texture/exit.xpm"
# define DOOR "./Texture/door.xpm"
# define MAX_RESOURCE 128

# define ALL_CHARS	"_01NSEW"
# define IN_CHARS	"0NSEW"
# define DIRS		"NSEW"

# define WALL "./Texture/wall.xpm"
# define NO "./Texture/NO.xpm"
# define SO "./Texture/SO.xpm"
# define WE "./Texture/WE.xpm"
# define EA "./Texture/EA.xpm"

enum			e_sound
{
	Sound_None,
	Sound_D1,
	Sound_Num
};

enum		e_game
{
	Win_x = 1000,
	Win_y = 600,
	Fov = 60
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
	char		*tmp;
	char		**matrix;
	char		**map;
}				t_map;

typedef struct s_img
{
	void		*img;
	void		*wall;
}				t_img;

typedef struct s_ray
{
	double			x;
	double			y;
	double		r_cos;
	double		r_sin;
	double		height;
	double		distance;
}				t_ray;

typedef struct s_player
{
	t_ray		ray;
	double		angle;
	double			x;
	double			y;
}				t_player;

typedef struct s_all
{
	void		*mlx;
	void		*win;
	// char	(*identifier)[13];
	char		**identifier;
	char		**matrix;
	t_map		map;
	t_img		img;
	t_player	player;
	t_resources	resource;
}				t_all;

//MATRIX ????
void	get_matrix(t_all *all, const char	*mpath, int line_len);
void	get_elems(char *line, char	**first, char **second);
void	ft_matrix(t_all *all, const char *mpath);
void	set_identifers(t_all *all);
int		ft_count_lines(const char *mpath);
int		valid_identifiers(char	**identifier);
char	*get_identifier(char	**identifier, char	*idtf);

//MAP ????
void	ft_fill_space(t_map *map);
void	ft_check_wall(t_map *map);
void	ft_check_map(t_map *map);
void	ft_check_split(t_map *map, char *str);
int		ft_check_char(char *map, char *symbol);

//UTILES ????
void	ft_error(char *str);
int		ft_free_array(char **c);
size_t	ft_strnlen(const char *str, char c);
char	*read_arg(char *s1, char *s2, char **ret);

//SOUNDS ????
void	sound_init(t_all *all);
void	sound_stop(t_all *all, int sound);
void	sound_play(t_all *g, int sound, t_bool loop);

char	*get_next_line(int fd);

#endif
