#include "../include/cub.h"

void check_map_args(t_map *map)
{
    int fd;
    int lines_nb = 0;
    int i = 0;

    fd = open("example.cub", O_RDONLY);

    map->map = malloc(sizeof(char *) * 100);
    map->map[i] = get_next_line(fd);
    while (map->map[i])
	{
		map->map[++i] = get_next_line(fd);
		lines_nb++;
	}
	close(fd);
}