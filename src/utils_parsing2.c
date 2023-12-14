#include "../include/cub3D.h"

// void	print_map(char **map)
// {
//     printf("Printing map...\n");

//     if (map == NULL) 
//     {
//         printf("map->only_map is NULL\n");
//         return;
//     }
//     for (int i = 0; map[i] != NULL; i++)
//     {
//         printf("map %i : %s\n", i,  map[i]);
//     }
// }

int	count_map_size(t_map *map, int fd)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		if (i >= map->start_map_index)
			j++;
		i++;
		line = get_next_line(fd);
	}
	return (j);
}

int	count_file_size(int fd)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		i++;
		line = get_next_line(fd);
	}
	return (i);
}
