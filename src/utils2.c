#include "../include/cub3D.h"

void	init_cub(t_cub *cub)
{
	ft_bzero(cub, sizeof(t_cub));
	cub->v.pos[0] = (double)5 / 8 + 0.5;
	cub->v.pos[1] = (double)5 / 8 + 0.5;
	cub->v.step[0] = 1;
	cub->v.step[1] = 1;
	cub->v.camangle = 0.5;
	// for the direction
	cub->v.playerdir[0] = 1;
	cub->v.camplane[1] = -0.66;
	cub->v.movespeed = 0.00007;
	cub->v.rotspeed = 0.00004;
	cub->mapheight = 8;
	cub->mapwidth = 8;
	cub->ceiling = get_color(1, 1, 50, 255);
	cub->floor = get_color(0, 100, 0, 255);
}