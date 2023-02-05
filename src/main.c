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
	// printf("all->player.ray.angle = %f\n", all->player.ray.angle);
	all->comp.ray_angle = all->player.ray.angle;
	if (all->player.ray.angle >= 90 && all->player.ray.angle <= 180)
		all->comp.ray_angle = ft_fabs(180 - all->player.ray.angle);
	else if (all->player.ray.angle >= 180 && all->player.ray.angle <= 270)
		all->comp.ray_angle = ft_fabs(all->player.ray.angle - 180);
	else if (all->player.ray.angle >= 270 && all->player.ray.angle <= 360)
		all->comp.ray_angle = ft_fabs(360 - all->player.ray.angle);
	// printf("degree_to_radians =%f\n", all->comp.dx * tan(degree_to_radians(all->player.ray.angle)));
	// printf("tan(degree_to_radians(all->player.ray.angle)= %f\n", tan(degree_to_radians(all->player.ray.angle)));
	// printf("stex = %f\n", all->comp.ray_angle);
	// printf("stex = %d\n", (int)all->comp.ray_angle);
	// printf("all->player.ray.angle  = %f\n", all->player.ray.angle);
	// printf("all->player.ray.angle  = %\n", (int)all->player.ray.angle);
	if (all->player.ray.angle == 0
		|| all->player.ray.angle == 360
		|| all->player.ray.angle == 180)
	{
		// printf("stex\n");
		all->comp.y_step = 0;
		all->comp.x_step = Field;
		all->comp.y_intercept = all->player.y;
		all->comp.x_intercept = all->player.x + (all->comp.dx * all->comp.tile_step_x);
	}
	else if (all->player.ray.angle == 90
		|| all->player.ray.angle == 270)
	{
		all->comp.bool = 1;
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
	// printf("(all->comp.dy / tan(degree_to_radians(all->player.ray.angle))) * all->comp.tile_step_x = %f\n", (all->comp.dy / tan(degree_to_radians(all->player.ray.angle))) * all->comp.tile_step_x);
	// printf("%f\n", (dx / tan(degree_to_radians(ray_angle))));
	// printf("tan = %f\n", -50/tan(degree_to_radians(30)));
	// printf("stex = %f\n", all->comp.dx * tan(degree_to_radians(all->comp.ray_angle)));
	// printf("all->player.x = %f\n", all->player.x);
	// printf("all->player.y = %f\n", all->player.y);
	// printf("ray_angle_tmp = %f\n", ray_angle);
	// printf("ray_angle = %f\n", all->player.ray.angle);
	// printf("dx = %d\n", all->comp.dx);
	// printf("dy = %d\n", all->comp.dy);
	// printf("------------------------------\n");
	// printf("all->player.angle = %f\n", all->player.angle);
	// printf("comp ray_angle = %f\n", all->comp.ray_angle);
	// printf("all->player.ray.angle= %f\n", all->player.ray.angle);
	// printf("x_step = %f\n", all->comp.x_step);
	// printf("y_step = %f\n", all->comp.y_step);
	// printf("x_inter = %f\n", all->comp.x_intercept);
	// printf("y_inter = %f\n", all->comp.y_intercept);
	// printf("*******************************\n");
	// printf("tile_step_x = %d\n", all->comp.tile_step_x);
	// printf("tile_step_y = %d\n", all->comp.tile_step_y);
	// printf("%f\n", floor(all->player.x / Field));
	return (0);
}

void	field_len(double intercept, t_component *comp, int img_height)
{
	double	tmp;

	tmp = intercept - (((int)intercept / Field) * Field)/** (img_height / comp->height_wall)*/;
	comp->pic_x = tmp * ((img_height) / (double)Field);
	if ((int)comp->height_wall > Win_y)
	{
		// printf("x = %f\n", player.x);
		// printf("y = %f\n", player.y);
		comp->pic_y = (((double)(comp->height_wall) - (double)Win_y) / (double)2) * ((double)img_height / (double)comp->height_wall);
		// printf("comp->pic_y  = %lf\n", comp->pic_y);
		// printf("  comp->height_wall = %lf\n",  comp->height_wall);
		comp->pic_y_step = (img_height -  (comp->pic_y  * 2)) / Win_y;
		// comp->pic_y_step =1;
		// printf("comp->pic_y_step  = %f\n", comp->pic_y_step);
	}
	else
	{
		comp->pic_y = 0;
		comp->pic_y_step = img_height / comp->height_wall;
	}
	// tmp = all->comp.y_intercept - (((int)all->comp.y_intercept / Field) * Field)/** (all->img_height / all->comp.height_wall)*/;
	// 		// printf("tmp  = %lf\n", tmp);
	// 		// printf("all->comp.y_intercept  = %lf\n", all->comp.y_intercept);
	// 		all->comp.pic_x = tmp * ((all->img_height) / (double)Field);
	// 		if ((int)all->comp.height_wall > Win_y)
	// 		{
	// 			// printf("x = %f\n", all->player.x);
	// 			// printf("y = %f\n", all->player.y);
	// 			all->comp.pic_y = (((double)(all->comp.height_wall) - (double)Win_y) / (double)2) * ((double)all->img_height / (double)all->comp.height_wall);
	// 			// printf("all->comp.pic_y  = %lf\n", all->comp.pic_y);
	// 			// printf("  all->comp.height_wall = %lf\n",  all->comp.height_wall);
	// 			all->comp.pic_y_step = (all->img_height -  (all->comp.pic_y  * 2)) / Win_y;
	// 			// all->comp.pic_y_step =1;
	// 			// printf("all->comp.pic_y_step  = %f\n", all->comp.pic_y_step);
	// 		}
	// 		else
	// 		{
	// 			all->comp.pic_y = 0;
	// 			all->comp.pic_y_step = all->img_height / all->comp.height_wall;
	// 		}
}

int	get_distance(t_all *all);

double ray_distance(t_all *all)
{
	double	tmp;
	double current_distance;;
	double correct_distance;;
	if (get_distance(all) == HORIZ)
	{
		// printf("horiz\n");
		// all->comp.bool = 2;
		// printf("---------------------------------\n");
		// printf("horiz\n");
		// printf("player.x = %f\n", all->player.x);
		// printf("player.y = %f\n", all->player.y);
		// printf("all->comp.ray_angle = %f\n", all->comp.ray_angle);
		// printf(" all->player.ray.angle = %f\n", all->player.ray.angle);
		// printf("dx = %f\n", all->comp.dx);
		// printf("dy = %f\n", all->comp.dy);
		// printf("x_intercept = %f\n", all->comp.x_intercept);
		// printf("y_intercept = %f\n", all->comp.y_intercept);
		// printf("x_int_wall = %d\n", all->comp.x_int_wall);
		// printf("y_int_wall = %d\n", all->comp.y_int_wall);
		// printf("y_tile_wall = %d\n", all->comp.y_tile_wall);
		// printf("x_tile_wall = %d\n", all->comp.x_tile_wall);
		// printf("x_step = %f\n", all->comp.x_step);
		// printf("y_step = %f\n", all->comp.y_step);
		// printf("*******************************\n");
		current_distance = sqrt(pow(ft_fabs(all->player.x - all->comp.x_intercept), 2)
		+ pow(ft_fabs(all->player.y - (all->comp.y_int_wall * Field)), 2));
		correct_distance = current_distance * cos(degree_to_radians(all->player.ray.angle - all->player.angle));
		all->comp.height_wall = (((double)((double)Win_y * (double)Field) / (double)2) / correct_distance);
		if (all->player.ray.angle >= 0 && all->player.ray.angle <= 180)
		{
			tmp = all->comp.x_intercept - (((int)all->comp.x_intercept / Field) * Field)/** (all->img_height / all->comp.height_wall)*/;
			all->comp.pic_x = tmp * ((all->img_height) / (double)Field);
			if ((int)all->comp.height_wall > Win_y)
			{
				// printf("x = %f\n", all->player.x);
				// printf("y = %f\n", all->player.y);
				all->comp.pic_y = (((double)(all->comp.height_wall) - (double)Win_y) / (double)2) * ((double)all->img_height / (double)all->comp.height_wall);
				// printf("all->comp.pic_y  = %lf\n", all->comp.pic_y);
				// printf("  all->comp.height_wall = %lf\n",  all->comp.height_wall);
				all->comp.pic_y_step = (all->img_height -  (all->comp.pic_y  * 2)) / Win_y;
				// all->comp.pic_y_step =1;
				// printf("all->comp.pic_y_step  = %f\n", all->comp.pic_y_step);
			}
			else
			{
				all->comp.pic_y = 0;
				all->comp.pic_y_step = all->img_height / all->comp.height_wall;
			}
		}
		else
		{
			tmp = (((int)(all->comp.x_intercept / (double)Field) + 1) * Field) - all->comp.x_intercept;
			all->comp.pic_x = tmp * ((all->img_height) / (double)Field) /* * (all->img_height / all->comp.height_wall)*/;
			// printf("tmp = %lf\n", tmp);
			// printf("all->comp.pic_x = %lf\n", all->comp.pic_x);
			if ((int)all->comp.height_wall > Win_y)
			{
				all->comp.pic_y = (((double)(all->comp.height_wall) - (double)Win_y) / (double)2) * ((double)all->img_height / (double)all->comp.height_wall);
				all->comp.pic_y_step = (all->img_height -  (all->comp.pic_y  * 2)) / Win_y;
				// all->comp.pic_y_step =1;
			}
			else
			{
				all->comp.pic_y = 0;
				all->comp.pic_y_step = all->img_height / all->comp.height_wall;
			}
			// printf("all->comp.pic_y = %lf\n", all->comp.pic_y);
			// printf("all->comp.pic_y_step = %lf\n", all->comp.pic_y_step);
		}
	}
	else
	{
		// printf("---------------------------------\n");
		// printf("vert\n");
		// printf("player.x = %f\n", all->player.x);
		// printf("player.y = %f\n", all->player.y);
		// printf("all->comp.ray_angle = %f\n", all->comp.ray_angle);
		// printf(" all->player.ray.angle = %f\n", all->player.ray.angle);
		// printf("dx = %f\n", all->comp.dx);
		// printf("dy = %f\n", all->comp.dy);
		// printf("x_intercept = %f\n", all->comp.x_intercept);
		// printf("y_intercept = %f\n", all->comp.y_intercept);
		// printf("x_int_wall = %d\n", all->comp.x_int_wall);
		// printf("y_int_wall = %d\n", all->comp.y_int_wall);
		// printf("y_tile_wall = %d\n", all->comp.y_tile_wall);
		// printf("x_tile_wall = %d\n", all->comp.x_tile_wall);
		// printf("x_step = %f\n", all->comp.x_step);
		// printf("y_step = %f\n", all->comp.y_step);
		// printf("*******************************\n");
		// current_distance = sqrt(pow(ft_fabs(all->player.x - all->comp.x_intercept), 2)
		// + pow(ft_fabs(all->player.y - (all->comp.y_int_wall * Field)), 2));
		// correct_distance = current_distance * cos(degree_to_radians(all->player.ray.angle - all->player.angle));
		// all->comp.height_wall = (((double)((double)Win_y * (double)Field) / (double)2) / correct_distance);
		current_distance = sqrt(pow(ft_fabs(all->player.x - all->comp.x_int_wall * Field), 2) 
		+ pow(ft_fabs(all->player.y - all->comp.y_intercept), 2));
		correct_distance = current_distance * cos(degree_to_radians(all->player.ray.angle - all->player.angle));
		all->comp.height_wall = (((double)((double)Win_y * (double)Field) / (double)2) / correct_distance);
		// all->comp.height_wall = floor(((float)(Win_y * Field) / 2) / all->player.ray.distance);
		if (all->player.ray.angle >= 90 && all->player.ray.angle <= 270)
		{
			field_len(all->comp.y_intercept, &all->comp, all->img_height);
			tmp = (((int)(all->comp.y_intercept / (double)Field) + 1) * Field) - all->comp.y_intercept;
			all->comp.pic_x = tmp * ((all->img_height) / (double)Field);

				// printf("x = %f\n", all->player.x);
				// printf("y = %f\n", all->player.y);
			if ((int)all->comp.height_wall > Win_y)
			{
				all->comp.pic_y = (((double)(all->comp.height_wall) - (double)Win_y) / (double)2) * ((double)all->img_height / (double)all->comp.height_wall);
				all->comp.pic_y_step = (all->img_height -  (all->comp.pic_y  * 2)) / Win_y;
				// all->comp.pic_y_step =1;
			}
			else
			{
				all->comp.pic_y = 0;
				all->comp.pic_y_step = all->img_height / all->comp.height_wall;
			}
			// all->comp.pic_y = 0;
			// all->comp.pic_y_step =  ((double)all->img_height) / all->comp.height_wall;
		}
		else
		{
			field_len(all->comp.y_intercept, &all->comp, all->img_height);
			// tmp = all->comp.y_intercept - (((int)all->comp.y_intercept / Field) * Field)/** (all->img_height / all->comp.height_wall)*/;
			// // printf("tmp  = %lf\n", tmp);
			// // printf("all->comp.y_intercept  = %lf\n", all->comp.y_intercept);
			// all->comp.pic_x = tmp * ((all->img_height) / (double)Field);
			// if ((int)all->comp.height_wall > Win_y)
			// {
			// 	// printf("x = %f\n", all->player.x);
			// 	// printf("y = %f\n", all->player.y);
			// 	all->comp.pic_y = (((double)(all->comp.height_wall) - (double)Win_y) / (double)2) * ((double)all->img_height / (double)all->comp.height_wall);
			// 	// printf("all->comp.pic_y  = %lf\n", all->comp.pic_y);
			// 	// printf("  all->comp.height_wall = %lf\n",  all->comp.height_wall);
			// 	all->comp.pic_y_step = (all->img_height -  (all->comp.pic_y  * 2)) / Win_y;
			// 	// all->comp.pic_y_step =1;
			// 	// printf("all->comp.pic_y_step  = %f\n", all->comp.pic_y_step);
			// }
			// else
			// {
			// 	all->comp.pic_y = 0;
			// 	all->comp.pic_y_step = all->img_height / all->comp.height_wall;
			// }
			// printf("barev\n");
			// tmp = all->comp.y_intercept - (((int)all->comp.y_intercept / Field) * Field)/** (all->img_height / all->comp.height_wall)*/;
			// all->comp.pic_x = tmp * ((all->img_height) / (double)Field);
			// if ((int)all->comp.height_wall > Win_y)
			// {
			// 	all->comp.pic_y = (((double)(all->comp.height_wall) - (double)Win_y) / (double)2) * ((double)all->img_height / (double)all->comp.height_wall);
			// 	all->comp.pic_y_step = (all->img_height -  (all->comp.pic_y  * 2)) / Win_y;
			// 	// all->comp.pic_y_step =1;
			// }
			// else
			// {
			// 	all->comp.pic_y = 0;
			// 	all->comp.pic_y_step = all->img_height / all->comp.height_wall;
			// }
			// printf("all->comp.pic_y  = %lf\n", all->comp.pic_y);
			// printf("all->comp.pic_x  = %lf\n", all->comp.pic_x);
			// printf("  all->comp.height_wall = %lf\n",  all->comp.height_wall);
			// printf("all->comp.pic_y_step  = %f\n", all->comp.pic_y_step);
			// all->comp.pic_y = 0;
			// all->comp.pic_y_step = 1;
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
	int a = 0;
	while (1)
	{
		// if (a > 30)
		// {
		// 	printf("---------------------------------\n");
		// 	printf("vert\n");
		// 	printf("player.x = %f\n", all->player.x);
		// 	printf("player.y = %f\n", all->player.y);
		// 	printf("all->comp.ray_angle = %f\n", all->comp.ray_angle);
		// 	printf(" all->player.ray.angle = %f\n", all->player.ray.angle);
		// 	printf("dx = %f\n", all->comp.dx);
		// 	printf("dy = %f\n", all->comp.dy);
		// 	printf("x_intercept = %f\n", all->comp.x_intercept);
		// 	printf("y_intercept = %f\n", all->comp.y_intercept);
		// 	printf("x_int_wall = %d\n", all->comp.x_int_wall);
		// 	printf("y_int_wall = %d\n", all->comp.y_int_wall);
		// 	printf("y_tile_wall = %d\n", all->comp.y_tile_wall);
		// 	printf("x_tile_wall = %d\n", all->comp.x_tile_wall);
		// 	printf("x_step = %f\n", all->comp.x_step);
		// 	printf("y_step = %f\n", all->comp.y_step);
		// 	printf("*******************************\n");
		// 	printf("barev\n");
		// }
		// a++;
		// printf("barev\n");
		if (all->player.ray.angle >= 0 && all->player.ray.angle <= 180)
		{
			while((all->comp.y_intercept > (all->comp.y_int_wall * Field)))
			{
				// printf("%f\n", all->comp.y_intercept);
				// printf("%d\n", (int)all->comp.x_int_wall + all->comp.x_tile_wall);
				if (all->map.map[(int)all->comp.y_intercept / Field][(int)all->comp.x_int_wall + all->comp.x_tile_wall] != '0')
				{
					return (VERT);
				}
				all->comp.x_int_wall += all->comp.tile_step_x;
				all->comp.y_intercept += (all->comp.y_step * all->comp.tile_step_y);
			}
		}
		else
		{
			while((all->comp.y_intercept < (all->comp.y_int_wall * Field)))
			{
				if (all->map.map[(int)all->comp.y_intercept / Field][(int)all->comp.x_int_wall + all->comp.x_tile_wall] != '0')
				{
					return (VERT);
				}
				all->comp.x_int_wall += all->comp.tile_step_x;
				all->comp.y_intercept += (all->comp.y_step * all->comp.tile_step_y);
			}
		}
		if (all->player.ray.angle >= 90 && all->player.ray.angle <= 270)
		{
			while((all->comp.x_intercept > all->comp.x_int_wall * Field))
			{
				if (all->map.map[(int)all->comp.y_int_wall +  all->comp.y_tile_wall][(int)all->comp.x_intercept / Field] != '0')
				{
					return (HORIZ);
				}
				all->comp.y_int_wall += all->comp.tile_step_y;
				all->comp.x_intercept += (all->comp.x_step * all->comp.tile_step_x);
			}
		}
		else
		{
			while(all->comp.x_intercept < all->comp.x_int_wall * Field)
			{
				if (all->map.map[(int)all->comp.y_int_wall + all->comp.y_tile_wall][(int)all->comp.x_intercept / Field] != '0')
				{
					return (HORIZ);
				}
				all->comp.y_int_wall += all->comp.tile_step_y;
				all->comp.x_intercept += (all->comp.x_step * all->comp.tile_step_x);
			}
		}
	}
	return (0);
}

// void determine_img_pos(t_all *all, int *x, int *y, int flag)
// {


// }

int	get_color(t_data *data, int x, int y)
{
	char	*dst;
	// printf("x = %d\n", x);
	// printf("y = %d\n", y);
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(int *)dst);
}

int	get_right_color(t_data *data, int x, int y, t_all *all)
{
	// if (all->img_height >= all->comp.height_wall_test)
	// printf("x = %d\n", x);
	// printf("y = %d\n", y);
	// printf("all->comp.height_wall = %lf\n", all->comp.height_wall);
	// printf("y * (all->comp.height_wall / all->img_height) = %lf\n", (double)y * ((double)all->img_height) / all->comp.height_wall);
	// printf("%d\n", all->img_height);
		return (get_color(data, x /* (all->img_height / all->comp.height_wall) / Field*/, y/* * ((double)all->img_height) / all->comp.height_wall*/));
	// return (get_color(data, x * (all->comp.height_wall / all->img_height), y * (all->comp.height_wall_test / all->img_height)));
	// return (get_color(data, x, y));
	// return(1);
}

void ray_casting(t_all *all)
{
	all->comp.bool = 0;
	int			y_win;
	int			ray_count = 0;
	int			j = 0;

	all->player.ray.angle = all->player.angle;
	increament_in_range(360, all->half_fov, &all->player.ray.angle);
	all->img_data.img =  mlx_new_image(all->mlx, Win_x, Win_y);
	all->img_data.addr = mlx_get_data_addr(all->img_data.img, &all->img_data.bits_per_pixel, &all->img_data.line_length,
							&all->img_data.endian);
	int x = 0;
	int y = 0;
	while (ray_count < Win_x)
	{
		j = 0;
		all->player.ray.distance = ray_distance(all);
		all->comp.height_wall = ((float)(Win_y * Field) / 2) / all->player.ray.distance;
		// all->comp.height_wall = ((float)(Win_y * Field) / 2) / all->player.ray.distance;
		if (all->comp.height_wall >= Win_y || (int)all->player.ray.distance == 0)
		{
			// y = ft_fabs((Win_y - (all->player.ray.height * 2)) / 2);w
			// x = ft_fabs((Win_y - (all->player.ray.height * 2)) / 2);
			all->comp.height_wall = Win_y;
		}
		all->comp.half_height_wall = all->comp.height_wall / 2;
		// all->comp.height_wall_test = all->player.ray.height * 2;
		y_win = all->half_win_y - all->comp.half_height_wall;
		// printf("x = %d\n", all->comp.pic_x);
		// printf("x = %d\n", all->comp.pic_x);
		// printf(" all->comp.height_wall = %lf\n", all->comp.height_wall);
		while (y_win < all->half_win_y + all->comp.half_height_wall - 1)
		{
			// printf("all->comp.height_wall = %d\n", all->comp.height_wall);
			// // printf("ray_count = %d\n", ray_count);
			// printf(" all->comp.pic_x = %lf\n",  all->comp.pic_x);
			// printf(" all->comp.pic_y = %lf\n",  all->comp.pic_y);
			// printf(" y_win = %d\n",  y_win);
			my_mlx_pixel_put(&all->img_data, ray_count,  y_win, get_right_color(&all->img_no, all->comp.pic_x, all->comp.pic_y, all));
			y_win++;
			all->comp.pic_y += all->comp.pic_y_step;
			// printf("y = %d\n", all->comp.pic_y);
			// my_mlx_pixel_put(&all->img_data, ray_count,  all->comp.height_wall++, get_right_color(&all->img_no, x, y++, all));
			// my_mlx_pixel_put(&all->img_data, ray_count, all->comp.height_wall++, 0x000000FF);
			//  all->comp.height_wall++;
		}
		y = 0;
		ray_count += 1;
		// if ((int)all->player.angle - all->half_fov >= 0 && printf("if\n"))
		// 	all->player.ray.angle -= all->half_fov;
		// else
		// 	all->player.ray.angle = all->player.angle + 360 - all->half_fov;
		decreament_in_range(360, ((double)Fov / (double)Win_x), &all->player.ray.angle);
	}
	mlx_put_image_to_window(all->mlx, all->win, all->img_data.img, 0, 0);
}
