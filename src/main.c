#include "../include/cub3D.h"

void	test_textures(t_map *map)
{
	if (check_extension(map->NO_path, ".png") == -1 || \
		check_extension(map->SO_path, ".png") == -1 || \
		check_extension(map->WE_path, ".png") == -1 || \
		check_extension(map->EA_path, ".png") == -1)
	{
		set_error(map, "Bad texture extension", MAP_ERROR);
	}
	if (check_path(map->NO_path) == -1 || \
		check_path(map->SO_path) == -1 || \
		check_path(map->WE_path) == -1 || \
		check_path(map->EA_path) == -1)
	{
		set_error(map, "Failed to open texture path", MAP_ERROR);
	}
}

void	start_mlx(t_cub *cub)
{
	cub->mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "Minecraft", 0);
	if (!cub->mlx)
		set_error(cub, "Failed to initialize mlx", MLX_ERROR);
	cub->img = mlx_new_image(cub->mlx, SCREENWIDTH, SCREENHEIGHT);
	if (!cub->img)
		set_error(cub, "Failed to create image", MLX_ERROR);
	if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) == -1)
		set_error(cub, "Failed to place image on window", MLX_ERROR);
	mlx_loop_hook(cub->mlx, &main_loop, cub);
	mlx_close_hook(cub->mlx, &close_hook, cub);
	mlx_loop(cub->mlx);
}

void	parsing(t_map *map)
{
	check_map_args(map);
	get_texture_path(map);
	read_map(map);
	add_zero_map(map);
	findMapDimensions(map);
	findPlayerPosition(map);
	flood_fill(map, map->player_pos_x, map->player_pos_y);
	parse_rgb_values(map->f_rgb, map, 1);
	parse_rgb_values(map->c_rgb, map, 0);
	check_rgb_values(map);
	test_textures(map);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	ft_bzero(&cub, sizeof(t_cub));
	if (argc != 2)
	{
		printf("Error\nWrong number of arguments\n");
		exit(EXIT_FAILURE);
	}
	cub.map.map_path = argv[1];
	if (check_path(cub.map.map_path) == -1 || \
		check_extension(cub.map.map_path, ".cub") == -1)
	{
		printf("Error\nBad map\n");
		exit(EXIT_FAILURE);
	}
	parsing(&cub.map);
	init_cub(&cub);
	init_texture(&cub);
	start_mlx(&cub);
	exit_program(&cub);
}
