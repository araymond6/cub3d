#include "../include/cub3D.h"

void	keysHook(t_cub *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		closeHook(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		movePlayer(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		movePlayer(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
	{

	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
	{

	}
}