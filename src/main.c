#include "cub.h"

double	get_point_const(t_all *all)
{
	double	ray_angle = all->player.ray.angle;
	if (all->player.ray.angle == 0
		|| all->player.ray.angle == 360
		|| all->player.ray.angle == 180)
	{
		all->comp.y_step = Field;
		all->comp.x_step = Field;
		all->comp.y_intercept = all->player.y + (Field / 2);
		all->comp.x_intercept = all->player.x + (all->comp.dx * all->comp.tile_step_x);
	}
	else if (all->player.ray.angle == 90
		|| all->player.ray.angle == 270)
	{
		all->comp.y_step = Field;
		all->comp.x_step = Field;
		all->comp.x_intercept = all->player.x + (Field / 2);
		all->comp.y_intercept = all->player.y + (all->comp.dy * all->comp.tile_step_y);
	}
	else
	{
		all->comp.y_step = ft_fabs(tan(degree_to_radians(all->player.ray.angle)) * Field);
		all->comp.x_step = ft_fabs(Field / tan(degree_to_radians(all->player.ray.angle)));
		all->comp.x_intercept = all->player.x + ((all->comp.dy / tan(degree_to_radians(all->player.ray.angle))) * all->comp.tile_step_x);
		all->comp.y_intercept = all->player.y + (all->comp.dx * tan(degree_to_radians(all->player.ray.angle)) * all->comp.tile_step_y);
	}
	return(0);
}

double	get_componets(t_all *all)
{
	// adjust_dx_dy(&all->comp, all->player.angle, all->player.x, all->player.y);
	// adjust_tile_step(&all->comp, all->player.angle);
	double	x_step;
	double	y_step;
	double	x_intercept;
	double	y_intercept;
	double	ray_angle = all->player.ray.angle;

	if (ray_angle >= 90 && ray_angle <= 270)
	{
		all->comp.tile_step_x = -1;
		all->comp.dx = ft_fabs((((int)all->player.x / Field) * Field) - all->player.x);
	}
	else
	{
		all->comp.dx = ft_fabs((((int)(all->player.x / Field) * Field + Field) - all->player.x));
		all->comp.tile_step_x = 1;
	}
	if (ray_angle >= 0 && ray_angle <= 180)
	{
		all->comp.tile_step_y = -1;
		all->comp.dy = ft_fabs((all->player.y - ((int)(all->player.y / Field) * Field)));
	}
	else
	{
		all->comp.dy = ft_fabs((all->player.y - ((int)(all->player.y / Field) * Field + Field)));
		all->comp.tile_step_y = 1;
	}
	all->comp.ray_angle = all->player.ray.angle;
	if (all->player.ray.angle >= 90 && all->player.ray.angle <= 180)
		all->comp.ray_angle = ft_fabs(180 - all->player.ray.angle);
	else if (all->player.ray.angle >= 180 && all->player.ray.angle <= 270)
		all->comp.ray_angle = ft_fabs(all->player.ray.angle - 180);
	else if (all->player.ray.angle >= 270 && all->player.ray.angle <= 360)
		all->comp.ray_angle = ft_fabs(360 - all->player.ray.angle);
	if (all->player.ray.angle == 0
		|| all->player.ray.angle == 360
		|| all->player.ray.angle == 180)
	{
		all->comp.y_step = 0;
		all->comp.x_step = Field;
		all->comp.y_intercept = all->player.y;
		all->comp.x_intercept = all->player.x + (all->comp.dx * all->comp.tile_step_x);
	}
	else if (all->player.ray.angle == 90
		|| all->player.ray.angle == 270)
	{
		all->comp.y_step = Field;
		all->comp.x_step = 0;
		all->comp.x_intercept = all->player.x;
		all->comp.y_intercept = all->player.y + (all->comp.dy * all->comp.tile_step_y);
	}
	else
	{
		all->comp.y_step = ft_fabs(tan(degree_to_radians(all->comp.ray_angle)) * Field);
		all->comp.x_step = ft_fabs(Field / tan(degree_to_radians(all->comp.ray_angle)));
		all->comp.x_intercept = all->player.x + ft_fabs(all->comp.dy / tan(degree_to_radians(all->comp.ray_angle))) * all->comp.tile_step_x;
		all->comp.y_intercept = all->player.y + ft_fabs(all->comp.dx * tan(degree_to_radians(all->comp.ray_angle))) * all->comp.tile_step_y;
	}
	return (0);
}

double ray_distance(t_all *all)
{
	double	tmp;
	double current_distance;;
	double correct_distance;;
	if (get_distance(all) == HORIZ)
	{
		current_distance = sqrt(pow(ft_fabs(all->player.x - all->comp.x_intercept), 2)
		+ pow(ft_fabs(all->player.y - (all->comp.y_int_wall * Field)), 2));
		correct_distance = current_distance * cos(degree_to_radians(all->player.ray.angle - all->player.angle));
		all->comp.height_wall = (((double)((double)Win_y * (double)Field) / (double)2) / correct_distance);
		if (all->player.ray.angle >= 0 && all->player.ray.angle <= 180)
		{
			field_len(all->comp.x_intercept, &all->comp, all->imgs_wall[0].height, START_LEFT);
			all->comp.wall_index = 1;
		}
		else
		{
			field_len(all->comp.x_intercept, &all->comp, all->imgs_wall[0].height, START_RIGHT);
			all->comp.wall_index = 3;
		}
	}
	else
	{
		current_distance = sqrt(pow(ft_fabs(all->player.x - all->comp.x_int_wall * Field), 2) 
		+ pow(ft_fabs(all->player.y - all->comp.y_intercept), 2));
		correct_distance = current_distance * cos(degree_to_radians(all->player.ray.angle - all->player.angle));
		all->comp.height_wall = (((double)((double)Win_y * (double)Field) / (double)2) / correct_distance);
		if (all->player.ray.angle >= 90 && all->player.ray.angle <= 270)
		{
			field_len(all->comp.y_intercept, &all->comp, all->imgs_wall[0].height, START_LEFT);
			all->comp.wall_index = 0;
		}
		else
		{
			field_len(all->comp.y_intercept, &all->comp, all->imgs_wall[0].height, START_RIGHT);
			all->comp.wall_index = 2;
		}
	}
	return (correct_distance);
}

int	get_distance(t_all *all)
{
	double	ray_angle = all->player.ray.angle;
	all->comp.x_tile_wall = 0;
	all->comp.y_tile_wall = 0;
	all->player.ray.x = (int)all->player.x;
	all->player.ray.y = (int)all->player.y;
	if (ray_angle >= 90 && ray_angle <= 270)
	{
		all->comp.x_int_wall = (int)all->player.x / Field; // check 60
		all->comp.x_tile_wall = -1;
	}
	else
		all->comp.x_int_wall = (int)all->player.x / Field + 1; // check 60
	if (ray_angle >= 0 && ray_angle <= 180)
	{
		all->comp.y_tile_wall = -1;
		all->comp.y_int_wall = (int)all->player.y / Field;
	}
	else
		all->comp.y_int_wall = (int)all->player.y / Field + 1;
	get_componets(all);
	while (1)
	{
		if (all->player.ray.angle >= 0 && all->player.ray.angle <= 180)
		{
			while((all->comp.y_intercept > (all->comp.y_int_wall * Field)))
			{
				if (all->map.map[(int)all->comp.y_intercept / Field][(int)all->comp.x_int_wall + all->comp.x_tile_wall] != '0')
					return (VERT);
				all->comp.x_int_wall += all->comp.tile_step_x;
				all->comp.y_intercept += (all->comp.y_step * all->comp.tile_step_y);
			}
		}
		else
		{
			while((all->comp.y_intercept < (all->comp.y_int_wall * Field)))
			{
				if (all->map.map[(int)all->comp.y_intercept / Field][(int)all->comp.x_int_wall + all->comp.x_tile_wall] != '0')
					return (VERT);
				all->comp.x_int_wall += all->comp.tile_step_x;
				all->comp.y_intercept += (all->comp.y_step * all->comp.tile_step_y);
			}
		}
		if (all->player.ray.angle >= 90 && all->player.ray.angle <= 270)
		{
			while((all->comp.x_intercept > all->comp.x_int_wall * Field))
			{
				if (all->map.map[(int)all->comp.y_int_wall +  all->comp.y_tile_wall][(int)all->comp.x_intercept / Field] != '0')
					return (HORIZ);
				all->comp.y_int_wall += all->comp.tile_step_y;
				all->comp.x_intercept += (all->comp.x_step * all->comp.tile_step_x);
			}
		}
		else
		{
			while(all->comp.x_intercept < all->comp.x_int_wall * Field)
			{
				if (all->map.map[(int)all->comp.y_int_wall + all->comp.y_tile_wall][(int)all->comp.x_intercept / Field] != '0')
					return (HORIZ);
				all->comp.y_int_wall += all->comp.tile_step_y;
				all->comp.x_intercept += (all->comp.x_step * all->comp.tile_step_x);
			}
		}
	}
	return (0);
}

void draw_line(t_data *win_img_data, int x, int start_y, int end_y);

void ray_casting(t_all *all)
{
	int			y_win;
	int			ray_count = 0;

	all->player.ray.angle = all->player.angle;
	increament_in_range(360, all->half_fov, &all->player.ray.angle);
	if (all->win_img_data.img != NULL)
		mlx_destroy_image(all->mlx, all->win_img_data.img);
	all->win_img_data.img =  mlx_new_image(all->mlx, Win_x, Win_y);
	all->win_img_data.addr = mlx_get_data_addr(all->win_img_data.img, &all->win_img_data.bits_per_pixel, &all->win_img_data.line_length,
							&all->win_img_data.endian);
	adjust_dx_dy(&all->comp, all->player.angle, all->player.x, all->player.y);
	while (ray_count < Win_x)
	{
		adjust_tile_step(&all->comp, all->player.ray.angle);
		all->player.ray.distance = ray_distance(all);
		all->comp.height_wall = ((float)(Win_y * Field) / 2) / all->player.ray.distance;
		if (all->comp.height_wall >= Win_y || (int)all->player.ray.distance == 0)
			all->comp.height_wall = Win_y;
		all->comp.half_height_wall = all->comp.height_wall / 2;
		// y_win = 0;
		// while (y_win < all->half_win_y - all->comp.half_height_wall)
		// {
		// 	my_mlx_pixel_put(&all->win_img_data, ray_count,  y_win, 7293925);
		// 	y_win++;
		// }
		draw_line(&all->win_img_data, ray_count, 0, all->half_win_y - all->comp.half_height_wall);
		y_win = all->half_win_y - all->comp.half_height_wall;
		while (y_win < all->half_win_y + all->comp.half_height_wall)
		{
			if (all->comp.pic_y >= 1920)
				all->comp.pic_y = 1919;
			my_mlx_pixel_put(&all->win_img_data, ray_count,  y_win, get_color(&all->imgs_wall[all->comp.wall_index].data, all->comp.pic_x, all->comp.pic_y));
			y_win++;
			all->comp.pic_y += all->comp.pic_y_step;
		}
		y_win = all->half_win_y + all->comp.half_height_wall;
		// printf("y_win = %d\n", y_win);
		// draw_line(&all->win_img_data, ray_count, y_win, Win_y);
		while (y_win < Win_y)
		{
			my_mlx_pixel_put(&all->win_img_data, ray_count,  y_win, 12043420);
			y_win++;
		}
		ray_count += 1;
		decreament_in_range(360, ((double)Fov / (double)Win_x), &all->player.ray.angle);
	}
	mlx_put_image_to_window(all->mlx, all->win, all->win_img_data.img, 0, 0);
}

void draw_line(t_data *win_img_data, int x, int start_y, int end_y)
{
	start_y = 0;
	while (start_y < end_y)
	{
		my_mlx_pixel_put(win_img_data, x,  start_y, 7293925);
		start_y++;
	}
}
