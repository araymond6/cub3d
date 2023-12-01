#include "../include/cub3D.h"
//#include "../include/cub.h"

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
}

int main(int ac, char **av) //TODO: make sure all initial data is good
{
	t_cub cub;

	init_cub(&cub);
	init_texture(&cub);
	fill_map(&cub);
	cub.mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "Minecraft", 0);
	cub.img = mlx_new_image(cub.mlx, SCREENWIDTH, SCREENHEIGHT);
	mlx_image_to_window(cub.mlx, cub.img, 0, 0);
	mlx_loop_hook(cub.mlx, &main_loop, &cub);
	mlx_close_hook(cub.mlx, &close_hook, &cub);
	mlx_loop(cub.mlx);
	mlx_close_window(cub.mlx);
	mlx_terminate(cub.mlx);
}