/*
#include "cub.h"

void fill_back(void *mlx, void *mlx_win)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (i < Win_x)
	{
		while(j < Win_y / 2)
			mlx_pixel_put(mlx, mlx_win, i, j++, 0x00FF0000);
		i++;
		j = 0;
	}
	i = 0;
	j = Win_y / 2;
	while (i < Win_x)
	{
		while(j >= Win_y / 2 && j < Win_y)
			mlx_pixel_put(mlx, mlx_win, i, j++, 0x0000FF00);
		i++;
		j = Win_y / 2;
	}
}

double degree_to_radians(double a)
{
	return (a * (PI / 180));
}

int main()
{
    t_all all;
    all.player.x = 2.30;
    all.player.y = 5;

	int map[24][24]=
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	// double posX = 22, posY = 12;  //x and y start position
  	// double dirX = -1, dirY = 0; //initial direction vector

	void		*mlx;
	all.player.angle = 110;
	double		ray_angle = all.player.angle - (Fov / 2);
	int			ray_count = 0;
	void		*mlx_win;
	void		*img;
	double 		i = 0;
	mlx =  mlx_init();
	mlx_win = mlx_new_window(mlx, Win_x, Win_y, "cub3d");
	fill_back(mlx, mlx_win);
	printf("ray_angle = %f\n", ray_angle);
	printf("all.player.angle = %f\n", all.player.angle);
	while (ray_count < Win_x)
	{
		all.player.ray.x = all.player.x;
		all.player.ray.y = all.player.y;
		all.player.ray.r_cos = cos(degree_to_radians(ray_angle)) / 64;
		all.player.ray.r_sin = sin(degree_to_radians(ray_angle)) / 64;
		// printf("%f\n", ray_angle);
		// printf("all.player.ray.r_sin = %f\n", all.player.ray.r_sin);
		// printf("all.player.ray.r_cos = %f\n", all.player.ray.r_cos);

		all.player.ray.x += all.player.ray.r_cos;
		all.player.ray.y += all.player.ray.r_sin;
		while (map[(int)floor(all.player.ray.x)][(int)floor(all.player.ray.y)] != 1)
		{
			all.player.ray.x += all.player.ray.r_cos;
			all.player.ray.y += all.player.ray.r_sin;
		}
		all.player.ray.distance = sqrt(pow(all.player.x - all.player.ray.x, 2) + pow(all.player.y - all.player.ray.y, 2));
		// all.player.ray.distance = sqrt((all.player.x - all.player.ray.x) * (all.player.x - all.player.ray.x)
		//  + (all.player.y - all.player.ray.y) * (all.player.y - all.player.ray.y));
		// printf("%f\n", all.player.ray.distance);
		printf("ray_angle = %f\n", ray_angle);
		all.player.ray.distance = all.player.ray.distance * cos(degree_to_radians(ray_angle - all.player.angle));
		// printf("distance = %f\n", all.player.ray.distance);

		all.player.ray.height = floor(((float)Win_y / 2) / all.player.ray.distance);
		// printf("ray_count = %d\n", ray_count);
		// printf("degree_to_radians(ray_angle) = %f\n", degree_to_radians(ray_angle));
		// printf("all.player.ray.x = %f\n", all.player.ray.x);
		// printf("all.player.ray.y = %f\n", all.player.ray.y);
		// printf("all.player.ray.distance %f\n", all.player.ray.distance);
		// printf("height = %f\n", all.player.ray.height);
		// usleep(1000000);
		i = (Win_y / 2) - all.player.ray.height;
		while (i < (Win_y / 2) + all.player.ray.height)
			mlx_pixel_put(mlx, mlx_win, ray_count, i++, 0x000000FF);
		ray_count++;
		ray_angle += ((double)Fov / 1000.0);
	}
	mlx_loop(mlx);
}
*/