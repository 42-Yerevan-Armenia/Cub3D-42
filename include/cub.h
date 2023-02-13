/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:11:58 by arakhurs          #+#    #+#             */
/*   Updated: 2023/02/13 15:37:01 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libft/libft.h"
# include "../ft_fprintf/ft_printf.h"
# include "keys.h"
# include "defines.h"
# include <mlx.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <math.h>
# include <errno.h>

# define MAX_RESOURCE 128

typedef struct s_data
{
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
	Dis_wall = 0,
	Step_angle = 10,
	Step_walk = 100
};

enum			e_sound
{
	Sound_None,
	Sound_D1,
	Sound_I,
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
	int			m_i;
	int			m_j;
	int			p_x;
	int			p_y;
	int			v_x;
	int			v_y;
	double		s_x;
	double		s_y;
	int			width;
	int			height;
	int			coin;
	int			max;
	int			fd;
	char		*tmp;
	char		**matrix;
	char		**map;
	char		**mini;
	void		*minimap;
}				t_map;

typedef struct s_rgb
{
	char		*c_tx;
	char		*f_tx;
	int			r;
	int			g;
	int			b;
	int			val;
}				t_rgb;

typedef struct s_img
{
	int			width;
	int			height;
	t_data		data;
	t_rgb		floor;
	t_rgb		ceil;
	void		*img;
	char		*n_tx;
	char		*s_tx;
	char		*e_tx;
	char		*w_tx;
	void		*n_wall;
	void		*s_wall;
	void		*e_wall;
	void		*w_wall;
	void		*wall_tx;
	void		*floor_tx;
	void		*space_tx;
	void		*player_tx;
}				t_img;

typedef struct s_ray
{
	double		x;
	double		y;
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
	int		x_tile_wall;
	int		y_tile_wall;
	int		wall_index;
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
	int			p_i;
	int			p_j;
	char		p_in_map;
	double		angle;
	double		x;
	double		y;
}				t_player;

typedef struct s_all
{
	t_data		win_img_data;
	t_img		imgs_wall[4];
	int			img_width;
	int			img_height;
	void		*mlx;
	void		*win;
	char		**identifier;
	char		**matrix;
	int			half_fov;
	int			half_win_y;
	t_map		map;
	t_img		img;
	t_player	player;
	t_resources	resource;
	t_component	comp;
}				t_all;

//MATRIX 🧬
char	*get_identifier(char	**identifier, char	*idtf);
int		valid_identifiers(char	**identifier);
void	set_identifers(t_all *all);
void	ft_matrix(t_all *all, const char *mpath);

//MAP 🗺
void	ft_check_map(t_map *map, t_all *all);
int		ft_check_char(char *map, char *symbol);

//MATH 🧮
double	pov(char c);
double	ft_fabs(double a);
double	d_to_rdn(double a);
void	ft_to_integer(t_component *comp, int x, int y, int angle);
void	decreament_in_range(double range, double step, double *num);
void	increament_in_range(double range, double step, double *num);

//MOVES 🦶
int		event(int key, void *param);
void	adjust_tile_step(t_component *comp, double angle);
void	adjust_dx_dy(t_component *comp, double angle, double x, double y);

//RAY 🛤
int		is_odd_wall(double intercept);
int		get_distance(t_all *all);
void	ray_casting(t_all *all);
void	field_len(double intercept, t_component *comp, \
		int img_height, int flag);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		check_hit_vert(t_all *all);
int		check_hit_horiz(t_all *all);
void	get_componets(t_all *all);
int		get_intercept(t_all *all);
void	draw_line(t_data *win_img_data, int x, int start_y, \
		int end_y, int color);

// TEXTURES 🎨
void	ft_textures(t_all *all);
void	ft_textur_path(t_all *all);
int		get_color(t_data *data, int x, int y);
int		get_img(t_img *img, void *mlx, char	*img_path);

//UTILES 🛠
int		init(t_all *all);
int		check_ext(char *str);
int		ft_destroy(t_all *all);
int		ft_free_array(char **c);
int		ft_free_double(char ***ptr);
int		ft_fprintf(int fd, const char *from, ...);
void	ft_error(t_all *all, char *str);
char	*get_next_line(int fd);

//SOUNDS 🔊
void	music(t_all *all);
void	sound_init(t_all *all);
void	sound_stop(t_all *all, int sound);
void	sound_play(t_all *g, int sound, t_bool loop);

void	draw_minimap(t_all *all);

#endif
