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
		// all->comp.y_step = sqrt(pow(Field * fabs(tan(degree_to_radians(all->player.ray.angle))), 2) + pow(Field, 2));
		// all->comp.x_step = sqrt(pow(Field / fabs(tan(degree_to_radians(all->player.ray.angle))), 2) + pow(Field, 2));;
		all->comp.y_step = ft_fabs(tan(degree_to_radians(all->player.ray.angle)) * Field);
		all->comp.x_step = ft_fabs(Field / tan(degree_to_radians(all->player.ray.angle)));
		all->comp.x_intercept = all->player.x + ((all->comp.dy / tan(degree_to_radians(all->player.ray.angle))) * all->comp.tile_step_x);
		all->comp.y_intercept = all->player.y + (all->comp.dx * tan(degree_to_radians(all->player.ray.angle)) * all->comp.tile_step_y);
	}
	return(0);
}


double	get_componets(t_all *all)
{
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
		// printf("barev %d\n", all->comp.dx);
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
	if (ray_angle >= 90 && ray_angle <= 180)
		all->player.ray.angle = 180 - ray_angle;
	else if (ray_angle >= 180 && ray_angle <= 270)
		all->player.ray.angle = ray_angle - 180;
	else if (ray_angle >= 270 && ray_angle <= 360)
		all->player.ray.angle = 360 - ray_angle;
	// printf("degree_to_radians =%f\n", all->comp.dx * tan(degree_to_radians(all->player.ray.angle)));
	// printf("tan(degree_to_radians(all->player.ray.angle)= %f\n", tan(degree_to_radians(all->player.ray.angle)));
	// printf("stex = %f\n", ray_angle);
	if ((int)ray_angle == 0
		|| (int)ray_angle == 360
		|| (int)ray_angle == 180)
	{
		all->comp.y_step = 0;
		all->comp.x_step = Field;
		all->comp.y_intercept = all->player.y;
		all->comp.x_intercept = all->player.x + (all->comp.dx * all->comp.tile_step_x);
	}
	else if ((int)ray_angle == 90
		|| (int)ray_angle == 270)
	{
		all->comp.y_step = Field;
		all->comp.x_step = 0;
		all->comp.x_intercept = all->player.x;
		all->comp.y_intercept = all->player.y + (all->comp.dy * all->comp.tile_step_y);
		// printf("all->comp.y_intercept = %f\n", all->comp.y_intercept);
		// exit(1);
	}
	else
	{
		// all->comp.y_step = sqrt(pow(Field * fabs(tan(degree_to_radians(all->player.ray.angle))), 2) + pow(Field, 2));
		// all->comp.x_step = sqrt(pow(Field / fabs(tan(degree_to_radians(all->player.ray.angle))), 2) + pow(Field, 2));;
		all->comp.y_step = ft_fabs(tan(degree_to_radians(all->player.ray.angle)) * Field);
		all->comp.x_step = ft_fabs(Field / tan(degree_to_radians(all->player.ray.angle)));
		all->comp.x_intercept = all->player.x + ((all->comp.dy / tan(degree_to_radians(all->player.ray.angle))) * all->comp.tile_step_x);
		all->comp.y_intercept = all->player.y + (all->comp.dx * tan(degree_to_radians(all->player.ray.angle)) * all->comp.tile_step_y);
	}
	// printf("(all->comp.dy / tan(degree_to_radians(all->player.ray.angle))) * all->comp.tile_step_x = %f\n", (all->comp.dy / tan(degree_to_radians(all->player.ray.angle))) * all->comp.tile_step_x);
	// printf("%f\n", (dx / tan(degree_to_radians(ray_angel))));
	// printf("tan = %f\n", -50/tan(degree_to_radians(30)));
	// printf("all->player.x = %f\n", all->player.x);
	// printf("all->player.y = %f\n", all->player.y);
	// printf("ray_angel_tmp = %f\n", ray_angle);
	// printf("ray_angel = %f\n", all->player.ray.angle);
	// printf("dx = %d\n", all->comp.dx);
	// printf("dy = %d\n", all->comp.dy);
	// printf("x_step = %f\n", all->comp.x_step);
	// printf("y_step = %f\n", all->comp.y_step);
	// printf("x_inter = %f\n", all->comp.x_intercept);
	// printf("y_inter = %f\n", all->comp.y_intercept);
	// printf("tile_step_x = %d\n", all->comp.tile_step_x);
	// printf("tile_step_y = %d\n", all->comp.tile_step_y);
	// printf("%f\n", floor(all->player.x / Field));
	return (0);
}

int	get_distance(t_all *all);

double ray_distance(t_all *all)
{
	// printf("ray_distance\n");
	double current_distance;;
	double correct_distance;;
	if (get_distance(all) == 1)
	{
		// printf("all->player.y = %f\n", all->player.y);
		// printf("all->comp.y_int_wall * Field = %d\n", all->comp.y_int_wall * Field);
		// current_distance = sqrt(pow(ft_fabs(all->player.x - all->comp.x_intercept), 2) 
		// + pow(ft_fabs(all->player.y - (all->comp.y_int_wall * Field)), 2));
		correct_distance = ft_fabs(all->player.y - (all->comp.y_int_wall * Field));
	}
	else
	{
		// printf("all->player.x = %f\n", all->player.x);
		// printf("all->comp.x_int_wall * Field = %d\n", all->comp.x_int_wall * Field);
		correct_distance = ft_fabs(all->player.x - (all->comp.x_int_wall * Field));
	}
	// printf("ray_distance\n");
	return (correct_distance);
}

int	get_distance(t_all *all)
{
	double	ray_angle = all->player.ray.angle;
	// printf("ray_angle = %f\n",ray_angle );
	all->comp.x_tile_wall = 0;
	all->comp.y_tile_wall = 0;
	// all->player.ray.angle = all->player.angle - (Fov / 2);
	all->player.ray.x = (int)all->player.x;
	all->player.ray.y = (int)all->player.y;
	// all->comp.x_int_wall = (int)all->player.x / Field; // check 30
	// all->comp.y_int_wall = (int)all->player.y / Field;
	// printf("all->player.ray.angle  = %f\n", all->player.ray.angle);
	if (all->player.ray.angle >= 90 && all->player.ray.angle <= 270)
	{
		all->comp.x_int_wall = (int)all->player.x / Field; // check 60
		all->comp.x_tile_wall = -1;
	}
	else
		all->comp.x_int_wall = (int)all->player.x / Field + 1; // check 60
	if (all->player.ray.angle >= 0 && all->player.ray.angle <= 180)
	{
		all->comp.y_tile_wall = -1;
		all->comp.y_int_wall = (int)all->player.y / Field;
	}
	else
		all->comp.y_int_wall = (int)all->player.y / Field + 1;
	get_componets(all);
	// printf("\n\n\n\n\n\n\n\n\n\n");
	// printf("	all->comp.x_int_wall = %d\n", 	all->comp.x_int_wall);
	// printf(" 	all->comp.y_int_wall = %d\n",	all->comp.y_int_wall);
	// printf("	x_interceptl = %f\n", 	all->comp.x_intercept);
	// printf(" 	y_intercept = %f\n",	all->comp.y_intercept);
	// printf("	all->player.ray.x = %f\n", 	all->player.ray.x);
	// printf(" 	all->player.ray.y = %f\n",	all->player.ray.y);
	// printf("%f\n", all->player.angle);
	// printf("while_ in\n");
	while (1)
	{
		// while(all->comp.y_intercept > ((int)(all->player.ray.y / Field)) * Field)
		// {
		// printf("all->comp.y_intercept %f > all->comp.y_int_wall %d\n", all->comp.y_intercept , all->comp.y_int_wall * Field);
		// printf("all->comp.x_intercept %f < all->comp.x_int_wall %d\n", all->comp.x_intercept , all->comp.x_int_wall * Field);
		if (ray_angle >= 0 && ray_angle <= 180)
		{
			// printf("all->comp.y_intercept %f > all->comp.y_int_wall %d\n", all->comp.y_intercept , all->comp.y_int_wall * Field);
			while((all->comp.y_intercept > (all->comp.y_int_wall * Field) || all->comp.x_intercept == -1))
			{
				// printf("barev-------------------------------------\n");
				// printf("x_int_wall = %d\n", all->comp.x_int_wall + all->comp.x_tile_wall);
				// printf("(int)all->comp.y_intercept / Field = %d\n", (int)all->comp.y_intercept / Field);
				// printf("all->player.ray.angle = %f\n", all->player.ray.angle);
				if (all->map.map[(int)all->comp.y_intercept / Field][(int)all->comp.x_int_wall + all->comp.x_tile_wall] != '0')
				{
					// printf("all->player.x = %f\n", all->player.x);
					// printf("all->player.y = %f\n", all->player.y);
					// printf("vert\n");
	// printf("while\n");

					return (1);
				}
				all->comp.x_int_wall += all->comp.tile_step_x;
				all->comp.y_intercept += (all->comp.y_step * all->comp.tile_step_y);
			}
		}
		else if (all->comp.y_intercept != -1)
		{
			// printf("all->comp.y_intercept %f < all->comp.y_int_wall %d\n", all->comp.y_intercept , all->comp.y_int_wall * Field);
			while((all->comp.y_intercept < (all->comp.y_int_wall * Field)))
			{
				// printf("barev-------------------------------------\n");
				// printf("x_int_wall = %d\n", all->comp.x_int_wall + all->comp.x_tile_wall);
				// printf("(int)all->comp.y_intercept / Field = %d\n", (int)all->comp.y_intercept / Field);
				if (all->map.map[(int)all->comp.y_intercept / Field][(int)all->comp.x_int_wall + all->comp.x_tile_wall] != '0')
				{
					// printf("all->player.x = %f\n", all->player.x);
					// printf("all->player.y = %f\n", all->player.y);
					// printf("vert\n");
	// printf("while\n");

					return (2);
				}
				all->comp.x_int_wall += all->comp.tile_step_x;
				all->comp.y_intercept += (all->comp.y_step * all->comp.tile_step_y);
			}
		}
		// printf("all->comp.y_intercept %f > all->comp.y_int_wall %d\n", all->comp.y_intercept , all->comp.y_int_wall * Field);
		// printf("all->comp.x_intercept %f < all->comp.x_int_wall %d\n", all->comp.x_intercept , all->comp.x_int_wall * Field);
		// printf("%f\n", ray_angle);
		if (ray_angle >= 90 && ray_angle <= 270 && all->comp.x_intercept != -1)
		{
			// printf("all->comp.x_intercept %f > all->comp.x_int_wall %d\n", all->comp.x_intercept , all->comp.x_int_wall * Field);
			while((all->comp.x_intercept > all->comp.x_int_wall * Field  || all->comp.y_intercept == -1))
			{
				// printf("hajox ------------------------\n");
				// printf("(int)all->comp.x_intercept / Field = %d\n", (int)all->comp.x_intercept / Field);
				// printf("y_int_wall = %d\n", all->comp.y_int_wall + all->comp.y_tile_wall);
				if (all->map.map[(int)all->comp.y_int_wall +  all->comp.y_tile_wall][(int)all->comp.x_intercept / Field] != '0')
				{
					// printf("all->player.x = %f\n", all->player.x);
					// printf("all->player.y = %f\n", all->player.y);
					// printf("horiz\n");
	// printf("while\n");

					return (1);
				}
				all->comp.y_int_wall += all->comp.tile_step_y;
				all->comp.x_intercept += (all->comp.x_step * all->comp.tile_step_x);
			}
		}
		else if (all->comp.x_intercept != -1)
		{
			// printf("stex\n");
			// printf("all->comp.x_intercept %f < all->comp.x_int_wall %d\n", all->comp.x_intercept , all->comp.x_int_wall * Field);
			while(((all->comp.x_intercept < all->comp.x_int_wall * Field)  || all->comp.y_intercept == -1))
			{
				// printf("hajox ------------------------\n");
				// printf("(int)all->comp.x_intercept / Field = %d\n", (int)all->comp.x_intercept / Field);
				// printf("y_int_wall = %d\n", all->comp.y_int_wall + all->comp.y_tile_wall);
				if (all->map.map[(int)all->comp.y_int_wall + all->comp.y_tile_wall][(int)all->comp.x_intercept / Field] != '0')
				{
					// printf("all->player.x = %f\n", all->player.x);
					// printf("all->player.y = %f\n", all->player.y);
					// printf("all->comp.y_int_wall  = %d\n", all->comp.y_int_wall);
					// printf("horiz\n");
	// printf("while\n");

					return (1);
				}
				all->comp.y_int_wall += all->comp.tile_step_y;
				all->comp.x_intercept += (all->comp.x_step * all->comp.tile_step_x);
			}
		}
	}
	return (0);
}

void ray_casting(t_all *all)
{
	int			ray_count = Win_x - 1;
	double 		i = 0;
	int			j = 0;
	
	i = 4;

	// while (ray_count < Win_x)
	// {
	// 	get_distance(all);
	// 	all->player.ray.angle += ((double)Fov / 1000.0);
	// 	ray_count += 1;
	// }
	// if (get_distance(all) == 1)
	// {

	// }
	// else
	// {

	// }
	// fill_back(all->mlx, all->win);
	all->player.ray.angle = all->player.angle - (Fov / 2);
	all->img_data.img =  mlx_new_image(all->mlx, Win_x, Win_y);
	all->img_data.addr = mlx_get_data_addr(all->img_data.img, &all->img_data.bits_per_pixel, &all->img_data.line_length,
							&all->img_data.endian);
	while (ray_count >= 0)
	{
		j = 0;
		// printf("all->player.ray.angle = %f\n", all->player.ray.angle);
		// printf("all->player.ray.angle = %f\n", all->player.ray.angle);
		all->player.ray.distance = ray_distance(all);
		// printf("correct_distance = %f\n", all->player.ray.distance);
		all->player.ray.height = floor(((float)(Win_y * Field) / 2) / all->player.ray.distance);
		i = (Win_y / 2) - all->player.ray.height;
		while (j < i)
		{
			// mlx_pixel_put(all->mlx, all->win, ray_count, j++, 0x00FF0000);
			my_mlx_pixel_put(&all->img_data, ray_count, j++, 0x00FF0000);
		}
		j = i + all->player.ray.height * 2;
		while (j < Win_y)
		{
			// mlx_pixel_put(all->mlx, all->win, ray_count, j++, 0x0000FF00);
			my_mlx_pixel_put(&all->img_data, ray_count, j++, 0x0000FF00);
		}
		while (i < (Win_y / 2) + all->player.ray.height)
		{
			// mlx_pixel_put(all->mlx, all->win, ray_count, i++, 0x000000FF);
			my_mlx_pixel_put(&all->img_data, ray_count, i++, 0x000000FF);
		}
		ray_count--;
		all->player.ray.angle += ((double)Fov / 1000.0);
		// printf("ray_count = %d\n", ray_count);
	}
	 mlx_put_image_to_window(all->mlx, all->win, all->img_data.img, 0, 0);
}

// int main()
// {
//     t_all all;
// 	all.player.angle = 60;
//     all.player.x = (3 * Field) - (Field / 2);
//     all.player.y = (3 * Field) - (Field / 2);
// 	all.player.ray.angle = all.player.angle - (Fov / 2);
//     // all.player.x = 2;
//     // all.player.y = 5;

	// printf("all.player.x = %f\n", all.player.x);
	// printf("all.player.y = %f\n", all.player.y);
// 	// all.mlx =  mlx_init();
// 	// all.win = mlx_new_window(all.mlx, Win_x, Win_y, "cub3d");
// 	// event_listener(&all);
// 	// double x = 456;
// 	// double y = 431;
// 	// ft_to_integer(&x, &y, 361);
	// printf("x = %f\n", x);
	// printf("y = %f\n", y);
// 	ray_casting(&all);
// 	// mlx_hook(all.win, 17, 1L << 17, ft_close, &all);
// 	// mlx_loop(all.mlx);
// }
