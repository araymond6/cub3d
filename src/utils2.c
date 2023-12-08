#include "../include/cub3D.h"

void	init_cub(t_cub *cub) // TODO: move to utils
{
	cub->v.pos[0] = (double)5 / 8 + 0.5;
	cub->v.pos[1] = (double)5 / 8 + 0.5;
	cub->v.step[0] = 1;
	cub->v.step[1] = 1;
	cub->v.camangle = 0.5;

	// for the direction, to change when 
	cub->v.playerdir[1] = 0; // 0 for north & south
	cub->v.playerdir[0] = 1;
	cub->v.camplane[1] = -0.66;

	cub->v.movespeed = 0.00007;
	cub->v.rotspeed = 0.00006;
	cub->ceiling = get_color(cub->map.c_red, cub->map.c_green, cub->map.c_blue, 255);
	cub->floor = get_color(cub->map.f_red, cub->map.f_green, cub->map.f_blue, 255);
	printf("c: %d, %d, %d\n", cub->map.c_red, cub->map.c_green, cub->map.c_blue);
	printf("f: %d, %d, %d\n", cub->map.f_red, cub->map.f_green, cub->map.f_blue);
}

void	close_hook(void *param)
{
	t_cub	*cub;

	if (param)
		cub = param;
	mlx_delete_image(cub->mlx, cub->img);
	mlx_close_window(cub->mlx);
	mlx_terminate(cub->mlx);
	exit_program(cub);
}

