#include "../include/cub.h"
#define WIDTH 512
#define HEIGHT 512

int	get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int main()
{
    t_map map;
    map.map_path = "exemple.cub";
    check_map_args(&map);
	printf("yo\n");
}