#include "../include/cub3D.h"
#include "../include/cub.h"
#define WIDTH 1280
#define HEIGHT 720

#define screenWidth 640
#define screenHeight 480
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24

void	close_hook(void *param)
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

void	keys_hook(mlx_key_data_t keydata, void *param)
{
	t_cub	*cub;

	if (param)
		cub = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		close_hook(cub);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		cub->player.py += 2;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		cub->player.py -= 2;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		cub->player.px -= 2;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		cub->player.px += 2;
}

void	draw_shit(void *param)
{
	t_cub *cub;

	if (param)
		cub = param;
	draw_player(cub);
	mlx_key_hook(cub->mlx, &keys_hook, cub);
}

void	init_cub(t_cub *cub)
{
	ft_bzero(cub, sizeof(t_cub));
	cub->player.px = 300;
	cub->player.py = 300;
}

int main(int ac, char **av)
{
	t_cub cub;

	init_cub(&cub);
	cub.mlx = mlx_init(WIDTH, HEIGHT, "Minecraft", false);
	cub.img = mlx_new_image(cub.mlx, WIDTH, HEIGHT);
	mlx_loop_hook(cub.mlx, &drawFloor, &cub);
	
	mlx_close_hook(cub.mlx, &close_hook, &cub);
	mlx_loop(cub.mlx);
	mlx_close_window(cub.mlx);
	mlx_terminate(cub.mlx);

}