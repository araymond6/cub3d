#include "../include/cub3D.h"

void	start_mlx(t_cub *cub)
{
	cub->mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "Minecraft", 0);
	if (!cub->mlx)
		set_error(cub);
	cub->img = mlx_new_image(cub->mlx, SCREENWIDTH, SCREENHEIGHT);
	if (!cub->img)
		set_error(cub);
	if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) == -1)
		set_error(cub);
	mlx_loop_hook(cub->mlx, &main_loop, cub);
	mlx_close_hook(cub->mlx, &close_hook, cub);
	mlx_loop(cub->mlx);
}

int main()
{
	t_map map;
	t_cub cub;

	ft_bzero(&cub, sizeof(t_cub));
	map.map_path = "example.cub";
	check_map_args(&map);
	get_texture_path(&map);
	read_map(&map);
	parse_rgb_values(map.f_rgb,&map,1);
	parse_rgb_values(map.c_rgb,&map,0);

	//raycast initialization
	cub.map = map;
	init_cub(&cub);
	init_texture(&cub);
	start_mlx(&cub);

	return (0);
}

