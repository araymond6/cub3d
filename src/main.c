/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:45:48 by araymond          #+#    #+#             */
/*   Updated: 2023/12/15 14:22:09 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	check_count(t_map *map, int count)
{
	if (count > 1)
		set_error(map, "Duplicate path", MAP_ERROR);
}

void	test_textures(t_map *map)
{
	if (check_extension(map->no_path, ".png") == -1 || \
		check_extension(map->so_path, ".png") == -1 || \
		check_extension(map->we_path, ".png") == -1 || \
		check_extension(map->ea_path, ".png") == -1)
	{
		set_error(map, "Bad texture extension", MAP_ERROR);
	}
	if (check_path(map->no_path) == -1 || \
		check_path(map->so_path) == -1 || \
		check_path(map->we_path) == -1 || \
		check_path(map->ea_path) == -1)
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
	parse_rgb_values(map->f_rgb, map, 1);
	parse_rgb_values(map->c_rgb, map, 0);
	check_rgb_values(map);
	read_map(map);
	wrong_character_in_map(map);
	add_zero_map(map);
	find_map_dimensions(map);
	find_player_position(map);
	flood_fill(map, map->player_pos_x, map->player_pos_y);
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
