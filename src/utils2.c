#include "../include/cub3D.h"

void	set_direction(t_cub *cub)
{
	if (cub->map.playerdir == 'N')
	{
		cub->v.playerdir[1] = 0;
		cub->v.playerdir[0] = -1;
		cub->v.camplane[0] = -0.66;
	}
	else if (cub->map.playerdir == 'S')
	{
		cub->v.playerdir[1] = 0;
		cub->v.playerdir[0] = 1;
		cub->v.camplane[0] = 0.66;
	}
	else if (cub->map.playerdir == 'E')
	{
		cub->v.playerdir[1] = 0;
		cub->v.playerdir[0] = 1;
		cub->v.camplane[0] = 0;
		cub->v.camplane[1] = 0.66;
	}
	else if (cub->map.playerdir == 'W')
	{
		cub->v.playerdir[1] = 0;
		cub->v.playerdir[0] = -1;
		cub->v.camplane[0] = 0;
		cub->v.camplane[1] = -0.66;
	}
}

void	init_cub(t_cub *cub) // TODO: move to utils
{
	cub->v.pos[0] = (double)5 / 8 + 0.5;
	cub->v.pos[1] = (double)5 / 8 + 0.5;
	cub->v.step[0] = 1;
	cub->v.step[1] = 1;
	cub->v.camangle = 0.5;

	set_direction(cub);
	// for the direction, to change when 
	cub->v.playerdir[1] = 0; // 0 for north & south
	cub->v.playerdir[0] = 1;
	cub->v.camplane[1] = -0.66;

	cub->v.movespeed = 0.00007;
	cub->v.rotspeed = 0.00006;
	cub->ceiling = get_color(cub->map.c_red, cub->map.c_green, cub->map.c_blue, 255);
	cub->floor = get_color(cub->map.f_red, cub->map.f_green, cub->map.f_blue, 255);
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

