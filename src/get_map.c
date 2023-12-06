#include "../include/cub3D.h"


// Function to read the map from a file and update a t_map struct
void read_map(t_map *map)
{
    int	fd;
	int	lines_nb;
	int	i;

	lines_nb = 0;
	i = map->start_map_index;
	fd = open(map->map_path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	map->map = malloc(sizeof(char *) * 10000);
	map->map[i] = get_next_line(fd);
	while (map->map[i] && i < 100 - 1)
	{
		map->map[++i] = get_next_line(fd);
		lines_nb++;
        // printf("%s\n",map->start_map_index);
	}
	close(fd);
}
