#include "../include/cub3D.h"

void	init_cub(t_cub *cub) // TODO: move to utils
{
	ft_bzero(cub, sizeof(t_cub));
	cub->v.pos[0] = (double)5 / 8 + 0.5;
	cub->v.pos[1] = (double)5 / 8 + 0.5;
	cub->v.step[0] = 1;
	cub->v.step[1] = 1;
	cub->v.camangle = 0.5;
	// for the direction
	cub->v.playerdir[0] = 1;
	cub->v.camplane[1] = -0.66;
	cub->v.movespeed = 0.00007;
	cub->v.rotspeed = 0.00004;
	cub->mapheight = 8;
	cub->mapwidth = 8;
	cub->ceiling = get_color(1, 1, 50, 255);
	cub->floor = get_color(0, 100, 0, 255);
}

int main() 
{
    t_map map;
	t_cub cub;

    map.map_path = "example.cub";
    check_map_args(&map);

	fill_map(&cub);
    read_map(&map);
	init_cub(&cub);
	init_texture(&cub);
	cub.map = map;
	cub.mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "Minecraft", 0);
	cub.img = mlx_new_image(cub.mlx, SCREENWIDTH, SCREENHEIGHT);
	mlx_image_to_window(cub.mlx, cub.img, 0, 0);
	mlx_loop_hook(cub.mlx, &main_loop, &cub);
	mlx_close_hook(cub.mlx, &close_hook, &cub);
	mlx_loop(cub.mlx);
	mlx_close_window(cub.mlx);
	mlx_terminate(cub.mlx);
    get_texture_path(&map);

   // ------------ check rgb values for ceiling and floor-----------------
    // parse_rgb_values(map.f_rgb,&map,1);
    // parse_rgb_values(map.c_rgb,&map,0);
    // printf("Parsed Floor RGB values: Red: %d, Green: %d, Blue: %d\n", map.f_red, map.f_green, map.f_blue);
    // printf("Parsed Ceiling RGB values: Red: %d, Green: %d, Blue: %d\n", map.c_red, map.c_green, map.c_blue);
    //----------------------------------------------------------------------

    return 0;
}

