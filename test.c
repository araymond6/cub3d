#include "MLX42/include/MLX42/MLX42.h"
#include "include/cub3D.h"

void	closeHook(void *param);

char worldMap[mapWidth][mapHeight] = {
	{1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0 ,1},
	{1, 1, 0, 1, 0 ,1},
	{1, 0, 0, 1, 0 ,1},
	{1, 0, 0, 0, 0 ,1},
	{1, 1, 1, 1, 1, 1}
};

void castRays(void *param)
{
	t_cub	*cub;
	if (param)
		cub = param;
	cub->v.playerPos[0] = 5;
	cub->v.playerPos[1] = 5;
	cub->v.playerDir[0] = -1;
	cub->v.playerDir[1] = 0;
	cub->v.camPlane[0] = 0;
	cub->v.camPlane[1] = 0.66;
}

void	init_cub(t_cub *cub)
{
	ft_bzero(cub, sizeof(t_cub));
}

void	keyHook(void *param)
{
	t_cub	*cub;
	if (param)
		cub = param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		closeHook(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
	{
		printf("left\n");
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
	{
		printf("right\n");
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
	{
		printf("w\n");
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
	{
		printf("a\n");
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
	{
		printf("s\n");
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
	{
		printf("d\n");
	}
}

void	closeHook(void *param)
{
	t_cub	*cub;
	if (param)
		cub = param;
	mlx_close_window(cub->mlx);
	mlx_terminate(cub->mlx);
	exit(0);
}

int main()
{
	t_cub	cub;
	
	ft_bzero(&cub, sizeof(t_cub));
	cub.mlx = mlx_init(screenWidth, screenHeight, "Raycaster", 0);
	cub.img = mlx_new_image(cub.mlx, screenWidth, screenHeight);
	mlx_key_hook(cub.mlx, &keyHook, &cub);
	mlx_loop_hook(cub.mlx, &castRays, &cub);
	mlx_close_hook(cub.mlx, closeHook, &cub);
	mlx_loop(cub.mlx);

	return 0;
}
