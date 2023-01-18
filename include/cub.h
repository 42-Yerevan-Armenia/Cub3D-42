/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:11:58 by arakhurs          #+#    #+#             */
/*   Updated: 2023/01/18 18:12:50 by arakhurs         ###   ########.fr       */
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


# define PLAYER "Texture/exit.xpm"
# define DOOR "Texture/door.xpm"
# define MAX_RESOURCE 128

# define ALL_CHARS	"_01NSEW"
# define IN_CHARS	"0NSEW"
# define NO_DIRS	"_01"
# define DIRS		"NSEW"

# define WALL "Texture/wall.xpm"
# define NO "Texture/NO.xpm"
# define SO "Texture/SO.xpm"
# define WE "Texture/WE.xpm"
# define EA "Texture/EA.xpm"

enum			e_sound
{
	Sound_None,
	Sound_D1,
	Sound_Num
};

enum		e_game
{
	Win_x = 700,
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
	int			maps;
	char		*tmp;
	char		**matrix;
	char		**map;
}				t_map;

typedef struct s_img
{
	void		*img;
	void		*n_wall;
	void		*s_wall;
	void		*e_wall;
	void		*w_wall;
}				t_img;

typedef struct s_ray
{
	double		x;
	double		y;
	double		r_x;
	double		r_y;
	double		x_o;
	double		y_o;
	double		v_x;
	double		v_y;
	double		a;
	double		tan_a;
	int			depth;
	int			zeros;
	int			zerosh;
	
	double		r_cos;
	double		r_sin;
	double		wall_H;
	double		h;
	double		distance;
	double		column;
	double		row;


}				t_ray;

typedef struct s_player
{
	t_ray		ray;
	int			ray_count;
	char		p_in_map;
	int			p_x;
	int			p_y;
	double		p_a;
	int			p_r;
	double		dist;
	double		stepy;
	int			linelen;
	int			zeros;
	double		angle;
	double		distance;
	double		x;
	double		y;

	int		c[3];
	int		f[3];
	char	*addr[9];
	int		bits_per_pixel[9];
	int		line_length[9];
	int		endian[9];;
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

//MATRIX 🧬
void	get_matrix(t_all *all, const char	*mpath, int line_len);
void	get_elems(char *line, char	**first, char **second);
void	ft_matrix(t_all *all, const char *mpath);
void	set_identifers(t_all *all);
int		ft_count_lines(const char *mpath);
int		valid_identifiers(char	**identifier);
char	*get_identifier(char	**identifier, char	*idtf);

//MAP 🗺
void	ft_fill_space(t_map *map);
void	ft_check_wall(t_map *map);
void	ft_check_map(t_map *map, t_all *all);
void	ft_check_split(t_map *map, char *str);
int		ft_check_char(char *map, char *symbol);

//MATH 🧮
double	degree_to_radians(double a);
double	replace_angle_360(double a);
double	calc_dist(t_ray *ray);
void	pov(t_all *all);
void	ft_vertical_dist_check(t_all *all, char c);
int	create_trgb(int t, int r, int g, int b);

//MOVES 🦶
int		ft_key_press(int keycode, t_all *all);
void	ft_move_up(t_all *a);
void	ft_move_down(t_all *a);
void	ft_move_left(t_all *a);
void	ft_move_right(t_all *a);

//TEXTURES 🎨
int		ft_destroy(t_all *all);
void	ft_textures(t_all *all);

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

//RAY 🛤
void	raycast(t_all *all);
void	render(t_all *all);

#endif
