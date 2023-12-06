#include "../include/cub3D.h"

int main() 
{
    t_map map;
	t_cub cub;

	// //parsing functions
    // map.map_path = "example.cub";
    // check_map_args(&map);
    // get_texture_path(&map);
    // read_map(&map);

	//raycast initialization
	init_cub(&cub);
	init_texture(&cub);
	fill_map(&cub);

	//cub.map = map;
	cub.mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "Minecraft", 0);
	cub.img = mlx_new_image(cub.mlx, SCREENWIDTH, SCREENHEIGHT);
	mlx_image_to_window(cub.mlx, cub.img, 0, 0);
	mlx_loop_hook(cub.mlx, &main_loop, &cub);
	mlx_close_hook(cub.mlx, &close_hook, &cub);
	mlx_loop(cub.mlx);
	mlx_close_window(cub.mlx);
	mlx_terminate(cub.mlx);

   // ------------ check rgb values for ceiling and floor-----------------
    // parse_rgb_values(map.f_rgb,&map,1);
    // parse_rgb_values(map.c_rgb,&map,0);
    // printf("Parsed Floor RGB values: Red: %d, Green: %d, Blue: %d\n", map.f_red, map.f_green, map.f_blue);
    // printf("Parsed Ceiling RGB values: Red: %d, Green: %d, Blue: %d\n", map.c_red, map.c_green, map.c_blue);
    //----------------------------------------------------------------------

    return 0;
}

