/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:25:33 by arakhurs          #+#    #+#             */
/*   Updated: 2023/02/05 17:28:58 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	ft_destroy(t_all *all)
{
	mlx_destroy_window(all->mlx, all->win);
	//mlx_destroy_image(all->mlx, all->img->wall);
	sound_stop(all, 1);
	exit(EXIT_SUCCESS);
}

void	ft_win(t_all *all)
{
	all->mlx = mlx_init();
	if (all->mlx == NULL)
		ft_error("❌ Can't do it 🤣");
	all->win = mlx_new_window(all->mlx, 1800, 1024, "Title");
	if (all->win == NULL)
		ft_error("❌ Can't Creat Window 📺");
	all->img.img = mlx_new_image(all->mlx, 1800, 1024);
	mlx_hook(all->win, 17, 0, ft_destroy, all);
}

int	ft_key_press(int keycode, t_all *all)
{
	//char	c;
	if (keycode == 53)
		ft_destroy(all);
	return (0);
}

void	get_elems(char *line, char	**first, char **second)
{
	int	i;
	char	*res;
	char	*ptr_for_free;

	i = 0;
	while (line[i] && ft_strchr(SPACES, line[i]))
		i++;
	while (line[i] && !ft_strchr(SPACES, line[i]))
		i++;
	ptr_for_free = ft_substr(line, 0, i);
	*first = ft_strtrim(ptr_for_free, SPACES);
	ft_free_array(&ptr_for_free);
	ptr_for_free = ft_substr(line, i, ft_strlen(line));
	*second = ft_strtrim(ptr_for_free, SPACES);
	ft_free_array(&ptr_for_free);
}

char	*get_identifier(char	**identifier, char	*idtf)
{
	int		i;

	i = 0;
	while (identifier[i] && identifier[i + 1])
	{
		if (ft_strcmp(identifier[i], idtf) == 0)
			return (identifier[i + 1]);
		i += 2;
	}
	return (0);
}

void set_identifers(t_all *all)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = all->matrix;
	while(tmp[i] && i < 6)
	{
		get_elems(tmp[i], &all->identifier[j], &all->identifier[j + 1]);
		j += 2;
		i++;
	}
}

int	ft_check_extens(const char *mpath)
{
	if (ft_strlen(mpath) < 5
		|| ft_strcmp(".cub", (char *)mpath + (ft_strlen(mpath) - 4)) != 0)
	{
		ft_error("❌ Map format is not *.cub");
		return (1);
	}
	return (0);
}

int	ft_count_lines(const char *mpath)
{
	int		count;
	char	*line;
	int		fd;

	count = 0;
	fd = open(mpath, O_RDONLY);
	CHECK(fd);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		ft_free_array(&line);
		count++;

	}
	CHECK(close(fd));
	return (count);
}

void	get_matrix(t_all *all, const char	*mpath, int line_len)
{
	int		fd;
	char	*line;
	char	*ptr_for_free;
	int		i;
	int		flag = 0;
	
	i = 0;
	fd = (open(mpath, O_RDONLY));
	CHECK(fd);
	all->matrix = malloc(sizeof(char *) * (line_len + 1));
	while (1)
	{
		line = get_next_line(fd);
		ptr_for_free = ft_strtrim(line, SPACES);
		if (line == NULL && flag == 2)
		{
			ft_fprintf(2, "invalid map\n");
			exit(1);
		}
		else if (line == NULL || *ptr_for_free != '\0')
		{
			if (flag == 1)
				flag = 2;
			if (line != NULL)
				all->matrix[i++] = ft_strtrim(line, "\n");
			free(line);
		}
		else if (*ptr_for_free == '\0' && i > 6)
		{
			if (flag != 2)
				flag = 1;
		}
		ft_free_array(&ptr_for_free);
		if (line == NULL)
			break ;
	}
	all->matrix[i] = NULL;
	CHECK(close(fd));
}

void	ft_matrix(t_all *all, const char *mpath)
{
	char	*str;
	int		line_len;
	int		i;

	str = NULL;
	i = 0;
	ft_check_extens(mpath);
	line_len = ft_count_lines(mpath);
	// printf("%d\n", line_len);
	get_matrix(all, mpath, line_len);
	// ft_check_split(map, str);
	// ft_free_array(&str);
	// if (!(*(map->matrix)))
	// 	ft_error("❌ Can't split❗️");
	all->map.map = (all->matrix + 6);
	i = 0;
	while (all->map.map[i] && *all->map.map[i])
		printf("%s\n", all->map.map[i++]);
	// ft_check_map(&all->map);
}

double	get_player_angle(char	c)
{
	if (c == 'N')
		return (90.0);
	if (c == 'S')
		return (270.0);
	if (c == 'E')
		return (0.0);
	if (c == 'W')
		return (180.0);
	return (0.0);
}

void get_player_pos(char **map, double *x, double *y, double *angle)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr(DIRS, map[i][j]))
			{
				*x = (j * Field) + (Field / 2);
				*y = (i * Field) + (Field / 2);
				*angle = get_player_angle(map[i][j]);
				map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

void	ft_textures(t_img *img, void *mlx)
{
	int	width;
	int	height;

	img->wall = mlx_xpm_file_to_image(mlx, WALL, &width, &height);
	if ((img->wall) == NULL)
		ft_error("❌ Can't Open Wall 🚧 Texture");
}

int	valid_identifiers(char	**identifier)
{
	int i;

	if (!get_identifier(identifier, "NO")
		|| !get_identifier(identifier, "SO")
		|| !get_identifier(identifier, "EA")
		|| !get_identifier(identifier, "WE")
		|| !get_identifier(identifier, "F")
		|| !get_identifier(identifier, "C"))
		return (1);
	return (0);
}

int get_img(t_img *img, void *mlx, char	*img_path)
{
	int	ret;

	ret = 0;
	img->img = mlx_xpm_file_to_image(mlx, img_path, &img->width, &img->height); // size - 1
	if (img->img == NULL && ++ret)
		ft_fprintf(2, "Cub3d : Error : %s : %s\n", img_path, strerror(errno));
	img->data.addr = mlx_get_data_addr(img->img, &img->data.bits_per_pixel, &img->data.line_length, &img->data.endian);
	if (img->data.addr == NULL && ++ret)
		ft_fprintf(2, "Cub3d : Error : %s : %s\n", img_path, strerror(errno));
	// img->width;
	// img->height;
	return (ret);
}

int init_img(t_all *all)
{
	if (get_img(&all->imgs_wall[0], all->mlx, WE)
		|| get_img(&all->imgs_wall[1], all->mlx, NO)
		|| get_img(&all->imgs_wall[2], all->mlx, EA)
		|| get_img(&all->imgs_wall[3], all->mlx, SO))
		return (1);
	return (0);
}

int init(t_all *all)
{
	if (init_img(all) == 1)
	{
		exit (1);
	}
	all->win_img_data.img = NULL;
	all->half_win_y = Win_y / 2;
	all->half_fov = Fov / 2;
	return (0);
}

int	main(int ac, char **av)
{
	t_all all;
	int		i = 0;

	if (ac == 2)
	{
		all.identifier = malloc(sizeof(char *) * 16);
		ft_memset(all.identifier, 0, sizeof(char *) * 16);
		ft_matrix(&all, av[1]);
		set_identifers(&all);
		get_player_pos(all.map.map, &all.player.x, &all.player.y, &all.player.angle);
		all.mlx =  mlx_init();
		all.win = mlx_new_window(all.mlx, Win_x, Win_y, "cub3d");
		init(&all);
		// // if (valid_identifiers(all.identifier) == 1
		// // 	&& ft_fprintf(2, "Error : invalid identifier\n"))
		// // 	exit (1);
		event_listener(&all);
		ray_casting(&all);
		mlx_hook(all.win, 17, 1L << 17, ft_close, &all);
		mlx_loop(all.mlx);
	}
	return 0;
}

// int main()
// {
// 	printf("%d\n", is_odd_wall(5564.2564));
// 	// double a = 1 / 100;
// 	// double b = tan(89.001);
// 	// printf("%lf\n", b);
// 	// if (b == 0)
// 	// 	printf("true");
// 	// b = 0;
// 	// if (b == 0)
// 	// 	printf("true");
// 	// printf("tan = %f\n", tan(0.000000001));
// 	// printf("sin = %f\n", sin(degree_to_radians(a)));
// 	// double angle = 350;
// 	// increament_in_range(360, ((double)Fov / 1000.0), &angle);
// 	// printf("((double)Fov / 1000.0) = %f\n", ((double)Fov / 1000.0));
// 	// increament_in_range(360, 30, &angle);
// 	// printf("angle = %f\n", angle);
// }

