#include "../include/cub.h"

int	get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int main() {
    t_map map;
    map.map_path = "example.cub";
    check_map_args(&map);

    get_texture_path(&map);
    read_map(&map);

   // ------------ check rgb values for ceiling and floor-----------------
    // parse_rgb_values(map.f_rgb,&map,1);
    // parse_rgb_values(map.c_rgb,&map,0);
    // printf("Parsed Floor RGB values: Red: %d, Green: %d, Blue: %d\n", map.f_red, map.f_green, map.f_blue);
    // printf("Parsed Ceiling RGB values: Red: %d, Green: %d, Blue: %d\n", map.c_red, map.c_green, map.c_blue);
    //----------------------------------------------------------------------

    return 0;
}

