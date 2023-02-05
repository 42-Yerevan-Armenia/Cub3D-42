/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:11:58 by arakhurs          #+#    #+#             */
/*   Updated: 2023/02/05 17:07:17 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libft/libft.h"
# include "cub3d.h"
# include "keys.h"
# include <mlx.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <math.h>
# include "../libft/libft.h"


# define PLAYER "./Texture/exit.xpm"
# define DOOR "./Texture/door.xpm"
# define MAX_RESOURCE 128

# define ALL_CHARS	"_01NSEW"
# define IN_CHARS	"0NSEW"
# define DIRS		"NSEW"


# define WALL_NO	1
# define WALL_SO	2
# define WALL_WE	3
# define WALL_EA	4

# define HORIZ	1
# define VERT	2

# define WALL "./Texture/1.xpm"
# define NO "./wall_imgs/1.xpm"
# define SO "./wall_imgs/2.xpm"
# define WE "./wall_imgs/3.xpm"
# define EA "./wall_imgs/4.xpm"

# define START_LEFT	1
# define START_RIGHT 2


// # define START_LEFT	1
// # define START_RIGHT 2


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

enum		e_game
{
	Win_x = 1000,
	Win_y = 600,
	Fov = 60,
	Field = 1000,
	Dis_wall = 150,
	Step_angle = 1,
	Step_walk = 20
};

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
	char		*tmp;
	char		**matrix;
	char		**map;
}				t_map;

typedef struct s_img
{
	int			width;
	int			height;
	t_data		data;
	void		*img;
	void		*wall;
}				t_img;

typedef struct s_ray
{
	double		x;
	double		y;
	// int			x_int;
	// int			y_int;
	double		r_cos;
	double		r_sin;
	double		height;
	double		distance;
	double		angle;
}				t_ray;

typedef struct s_component
{
	int		tile_step_x;
	int		tile_step_y;
	int		x_int_wall;
	int		y_int_wall;
	int 	x_tile_wall;
	int 	y_tile_wall;
	int		wall_index;
	// int		wall;
	double	pic_x;
	double	pic_y;
	double	pic_y_step;
	double	height_wall;
	double	half_height_wall;
	double	height_wall_test;
	double	dx;
	double	dy;
	double	x_step;
	double	y_step;
	double	x_intercept;
	double	y_intercept;
	double	x_int_intercept;
	double	y_int_intercept;
	double	ray_angle;
	double	new_x;
	double	new_y;
}				t_component;

typedef struct s_player
{
	t_ray		ray;
	double		angle;
	double			x;
	double			y;
}				t_player;

typedef struct s_all
{
	t_data		win_img_data;
	t_img		imgs_wall[4];
	// t_img		img_so;
	// t_img		img_we;
	// t_img		img_ea;
	// void		*img_NO;
	// void		*img_SO;
	// void		*img_WE;
	// void		*img_EA;
	// void		*addr;
	int			img_width;
	int			img_height;
	void		*mlx;
	void		*win;
	// char	(*identifier)[13];
	char		**identifier;
	char		**matrix;
	int			half_fov;
	int			half_win_y;
	t_map		map;
	t_img		img;
	t_player	player;
	t_resources	resource;
	t_component comp;
}				t_all;

//MAP 🗺
void	ft_fill_space(t_map *map);
void	ft_check_wall(t_map *map);
void	ft_check_map(t_map *map);
void	ft_check_split(t_map *map, char *str);
int		ft_check_char(char *map, char *symbol);



//UTILES 🛠
void	ft_error(char *str);
int		ft_free_array(char **c);
size_t	ft_strnlen(const char *str, char c);
char	*read_arg(char *s1, char *s2, char **ret);

//SOUNDS 🔊
void	sound_init(t_all *all);
void	sound_stop(t_all *all, int sound);
void	sound_play(t_all *g, int sound, t_bool loop);

char	*get_next_line(int fd);
double	degree_to_radians(double a);
void	ft_to_integer(t_component *comp, int x, int y, int angle);
void	ray_casting(t_all *all);
int		get_distance(t_all *all);
double	ft_fabs(double a);
void	event_listener(t_all *all);
int		ft_close(t_all *all);
void	fill_back(void *mlx, void *mlx_win);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);


void	decreament_in_range(double range, double step, double *num);
void	increament_in_range(double range, double step, double *num);
int		get_color(t_data *data, int x, int y);
int		get_right_color(t_data *data, int x, int y, t_all *all);
int		is_odd_wall(double	intercept);
int		get_color(t_data *data, int x, int y);
void	adjust_tile_step(t_component *comp, double angle);
void	adjust_dx_dy(t_component *comp, double angle, double x, double y);
void	field_len(double intercept, t_component *comp, int img_height, int flag);

#endif
