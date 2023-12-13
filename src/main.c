#include "../include/cub3D.h"

void	start_mlx(t_cub *cub)
{
	cub->mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "Minecraft", 0);
	cub->img = mlx_new_image(cub->mlx, SCREENWIDTH, SCREENHEIGHT);
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
	mlx_loop_hook(cub->mlx, &main_loop, cub);
	mlx_close_hook(cub->mlx, &close_hook, cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
}

int main() 
{
	t_map map;
	t_cub cub;

	ft_bzero(&cub, sizeof(t_cub));
	//parsing functions
	map.map_path = "example.cub";
	check_map_args(&map);
	get_texture_path(&map);
	read_map(&map);
	add_zero_map(&map);
	findMapDimensions(&map);
	findPlayerPosition(&map);
	flood_fill(&map, map.player_pos_x, map.player_pos_y);

	//check rgb values for ceiling and floor
	//parse_rgb_values(map.f_rgb,&map,1);
	//parse_rgb_values(map.c_rgb,&map,0);
	//printf("Parsed Floor RGB values: Red: %d, Green: %d, Blue: %d\n", map.f_red, map.f_green, map.f_blue);
	//printf("Parsed Ceiling RGB values: Red: %d, Green: %d, Blue: %d\n", map.c_red, map.c_green, map.c_blue);

	//raycast initialization
	//cub.map = map;
	//init_cub(&cub);
	//init_texture(&cub);
	//printf("c: %d, %d, %d\n", cub.map.c_red, cub.map.c_green, cub.map.c_blue);
	//printf("f: %d, %d, %d\n", cub.map.f_red, cub.map.f_green, cub.map.f_blue);

	//start_mlx(&cub);
	//exit_program(&cub);

	return 0;
}

