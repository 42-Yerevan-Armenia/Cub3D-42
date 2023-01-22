#include "cub.h"

double	get_componets(t_all *all)
{
	double	x_step;
	double	y_step;
	double	x_intercept;
	double	y_intercept;

	all->comp.dy = (all->player.y - (floor(all->player.y / Field) * Field));
	all->comp.dx = ((round(all->player.x / Field) * Field) - all->player.x);
	// printf("degree_to_radians =%f\n", all->comp.dx * tan(degree_to_radians(all->player.ray.angle)));
	// printf("tan(degree_to_radians(all->player.ray.angle)= %f\n", tan(degree_to_radians(all->player.ray.angle)));
	if (all->player.ray.angle == 0 
		|| all->player.ray.angle == 180
		|| all->player.ray.angle == 90
		|| all->player.ray.angle == 270
		|| all->player.ray.angle == 360)
	{
		all->comp.y_step = 0;
		all->comp.x_step = 0;
	}
	else
	{
		// all->comp.y_step = sqrt(pow(Field * fabs(tan(degree_to_radians(all->player.ray.angle))), 2) + pow(Field, 2));
		// all->comp.x_step = sqrt(pow(Field / fabs(tan(degree_to_radians(all->player.ray.angle))), 2) + pow(Field, 2));;
		all->comp.y_step = tan(degree_to_radians(all->player.ray.angle)) * Field;
		all->comp.x_step = Field / tan(degree_to_radians(all->player.ray.angle));
	}
	all->comp.x_intercept = all->player.x + (all->comp.dy / tan(degree_to_radians(all->player.ray.angle)));
	all->comp.y_intercept = all->player.y - (all->comp.dx * tan(degree_to_radians(all->player.ray.angle)));
	// printf("%f\n", (dx / tan(degree_to_radians(ray_angel))));
	// printf("tan = %f\n", tan(degree_to_radians(30)));
	printf("all->player.x = %f\n", all->player.x);
	printf("all->player.y = %f\n", all->player.y);
	printf("ray_angel = %f\n", all->player.ray.angle);
	printf("dx = %d\n", all->comp.dx);
	printf("dy = %d\n", all->comp.dy);
	printf("x_step = %f\n", all->comp.x_step);
	printf("y_step = %f\n", all->comp.y_step);
	printf("x_inter = %f\n", all->comp.x_intercept);
	printf("y_inter = %f\n", all->comp.y_intercept);
	// printf("%f\n", floor(all->player.x / Field));
	return (0);
}

int	get_distance(t_all *all)
{
	int a = 5;
	// all->player.ray.angle = all->player.angle - (Fov / 2);
	all->player.ray.x = (int)all->player.x;
	all->player.ray.y = (int)all->player.y;
	// all->comp.x_int_wall = (int)all->player.x / Field; // check 30
	// all->comp.y_int_wall = (int)all->player.y / Field;
	all->comp.x_int_wall = (int)all->player.x / Field + 1; // check 60
	all->comp.y_int_wall = (int)all->player.y / Field;
	get_componets(all);
	// printf("\n\n\n\n\n\n\n\n\n\n");
	printf("	all->comp.x_int_wall = %d\n", 	all->comp.x_int_wall);
	printf(" 	all->comp.y_int_wall = %d\n",	all->comp.y_int_wall);
	// printf("	all->player.ray.x = %f\n", 	all->player.ray.x); 
	// printf(" 	all->player.ray.y = %f\n",	all->player.ray.y);
	// printf("%f\n", all->player.angle);
	while (a--)
	{
		// while(all->comp.y_intercept > ((int)(all->player.ray.y / Field)) * Field)
		// {
		printf("all->comp.y_intercept %f > all->comp.y_int_wall %d\n", all->comp.y_intercept , all->comp.y_int_wall * Field);
		printf("all->comp.x_intercept %f < all->comp.x_int_wall %d\n", all->comp.x_intercept , all->comp.x_int_wall * Field);
		while(all->comp.y_intercept > (all->comp.y_int_wall * Field))
		{
			printf("barev-------------------------------------\n");
			printf("x_int_wall = %d\n", all->comp.x_int_wall);
			printf("(int)all->comp.y_intercept / Field = %d\n", (int)all->comp.y_intercept / Field);
			if (all->map.map[(int)all->comp.y_intercept / Field][(int)all->comp.x_int_wall] != '0')
			{
				printf("vert\n");
			}
			all->comp.x_int_wall += 1;
			all->comp.y_intercept -= all->comp.y_step;
		}
		while(all->comp.x_intercept < all->comp.x_int_wall * Field)
		{
			printf("hajox ------------------------\n");
			printf("(int)all->comp.x_intercept / Field = %d\n", (int)all->comp.x_intercept / Field);
			printf("y_int_wall = %d\n", all->comp.y_int_wall - 1);
			if (all->map.map[(int)all->comp.y_int_wall - 1][(int)all->comp.x_intercept / Field] != '0')
			{
				printf("horiz\n");
				return (1);
			}
			all->comp.y_int_wall += -1;
			all->comp.x_intercept += all->comp.x_step;
		}
	}
	return (0);
}

void ray_casting(t_all *all)
{
	int			ray_count = 0;
	double 		i = 0;
	
	i = 4;

	// while (ray_count < Win_x)
	// {
		get_distance(all);
		// all->player.ray.angle += ((double)Fov / 1000.0);
		// ray_count += 1;
	// }
	// if (get_distance(all) == 1)
	// {

	// }
	// else
	// {

	// }
	// fill_back(all->mlx, all->win);
	// while (ray_count < 100)
	// {
		// all->player.ray.distance = all->player.ray.distance * cos(degree_to_radians(all->player.ray.angle - all->player.angle));
		// all->player.ray.height = floor(((float)Win_y / 2) / all->player.ray.distance);
		// // i = (Win_y / 2) - all->player.ray.height;
		// // while (i < (Win_y / 2) + all->player.ray.height)
		// // 	mlx_pixel_put(all->mlx, all->win, ray_count, i++, 0x000000FF);
		// ray_count++;
		// all->player.ray.angle += ((double)Fov / 1000.0);
	// }
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

// 	printf("all.player.x = %f\n", all.player.x);
// 	printf("all.player.y = %f\n", all.player.y);
// 	// all.mlx =  mlx_init();
// 	// all.win = mlx_new_window(all.mlx, Win_x, Win_y, "cub3d");
// 	// event_listener(&all);
// 	// double x = 456;
// 	// double y = 431;
// 	// ft_to_integer(&x, &y, 361);
// 	// printf("x = %f\n", x);
// 	// printf("y = %f\n", y);
// 	ray_casting(&all);
// 	// mlx_hook(all.win, 17, 1L << 17, ft_close, &all);
// 	// mlx_loop(all.mlx);
// }
