#include "../include/cub3D.h"
#include "../include/cub.h"

#define screenWidth 640
#define screenHeight 480
#define mapWidth 8
#define mapHeight 8

char	worldMap[mapWidth][mapHeight] = {
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1}
};

void	closeHook(void *param)
{
	t_cub	*cub;

	if (param)
		cub = param;
	mlx_close_window(cub->mlx);
}

void	initCub(t_cub *cub)
{
	ft_bzero(cub, sizeof(t_cub));
}

int main(int ac, char **av)
{
	t_cub cub;

	initCub(&cub);

	cub.map = worldMap;
	cub.mlx = mlx_init(screenWidth, screenHeight, "Minecraft", 0);
	cub.img = mlx_new_image(cub.mlx, screenWidth, screenHeight);
	mlx_loop_hook(cub.mlx, &mainLoop, &cub);
	mlx_close_hook(cub.mlx, &closeHook, &cub);
	mlx_loop(cub.mlx);
	mlx_close_window(cub.mlx);
	mlx_terminate(cub.mlx);

}