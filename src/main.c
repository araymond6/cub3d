#include "../include/cub3D.h"
#include "../include/cub.h"
#define WIDTH 1280
#define HEIGHT 720

#define screenWidth 640
#define screenHeight 480
#define texWidth 64
#define texHeight 64
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

void	new_image(t_cub *cub)
{
	mlx_delete_image(cub->mlx, cub->img);
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
}

void	keysHook(mlx_key_data_t keydata, void *param)
{
	t_cub	*cub;

	if (param)
		cub = param;
	
}

void	init_cub(t_cub *cub)
{
	ft_bzero(cub, sizeof(t_cub));
}

int main(int ac, char **av)
{
	t_cub cub;

	init_cub(&cub);
	cub.map = worldMap;
	cub.mlx = mlx_init(WIDTH, HEIGHT, "Minecraft", 0);
	cub.img = mlx_new_image(cub.mlx, WIDTH, HEIGHT);
	mlx_loop_hook(cub.mlx, &mainLoop, &cub);
	
	mlx_close_hook(cub.mlx, &closeHook, &cub);
	mlx_loop(cub.mlx);
	mlx_close_window(cub.mlx);
	mlx_terminate(cub.mlx);

}