#include "../include/cub3D.h"

void	test_textures(t_cub *cub)
{
	if (check_path(cub->map.NO_path) == -1 || \
		check_path(cub->map.SO_path) == -1 || \
		check_path(cub->map.WE_path) == -1 || \
		check_path(cub->map.EA_path) == -1)
	{
		cub->map.error = 1;
		exit_program(cub);
	}
}

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

int main(int argc, char **argv)
{
	t_map map;
	t_cub cub;

	ft_bzero(&cub, sizeof(t_cub));
	map.error = 0;
	map.map_path = argv[1];
	if (argc != 2)
	{
		printf("Error\nWrong number of arguments.\n");
		exit(1);
	}
	if (check_path(map.map_path) == -1)
	{
		printf("Error\nBad map path");
		exit(1);
	}
	check_map_args(&map);
	get_texture_path(&map);
	read_map(&map);
	add_zero_map(&map);
	findMapDimensions(&map);
	findPlayerPosition(&map);
	parse_rgb_values(map.f_rgb,&map,1);
	parse_rgb_values(map.c_rgb,&map,0);

	//raycast initialization
	cub.map = map;
	test_textures(&cub);
	init_cub(&cub);
	init_texture(&cub);
	start_mlx(&cub);

	return (0);
}

