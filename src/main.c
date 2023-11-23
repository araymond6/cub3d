#include "../include/cub3D.h"
#include "../include/cub.h"
#define WIDTH 1280
#define HEIGHT 720

int	get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

#define screenWidth 640
#define screenHeight 480
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24

void  drawBuffer(int *buffer)
{
	
}

int worldMap[mapWidth][mapHeight]=
{
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};


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

void	draw_player(t_cub *cub)
{
	int pcolor;
	int	i;
	int j;
	uint32_t	temp[2];

	new_image(cub);
	pcolor = get_rgba(255, 255, 0, 255);
	i = -1;
	temp[0] = cub->player.px;
	temp[1] = cub->player.py;
	while (++i < 16)
	{
		j = -1;
		while (++j < 16)
		{
			mlx_put_pixel(cub->img, cub->player.px, cub->player.py++, pcolor);
		}
		cub->player.px++;
		cub->player.py = temp[1];
	}
	cub->player.px = temp[0];
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
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
	
	t_map map;
    map.map_path = "exemple.cub";
    check_map_args(&map);

	init_cub(&cub);
	cub.mlx = mlx_init(WIDTH, HEIGHT, "Minecraft", false);
	cub.img = mlx_new_image(cub.mlx, WIDTH, HEIGHT);
	mlx_loop_hook(cub.mlx, &draw_shit, &cub);
	
	mlx_close_hook(cub.mlx, &close_hook, &cub);
	mlx_loop(cub.mlx);
	mlx_close_window(cub.mlx);
	mlx_terminate(cub.mlx);

}