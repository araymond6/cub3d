#include "../include/cub3D.h"

void print_map(char **map);

void read_map(t_map *map)
{
	int fd;
	int i;
	int j = 0;
	map->only_map = NULL;
	char *line;

	i = 0;
	fd = open(map->map_path, O_RDONLY);
	map->only_map = malloc(sizeof(char *) * MAX_LINES);
	if (map->only_map == NULL)
	{
		printf("Error\nMemory allocation error\n");
		exit(EXIT_FAILURE);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		if (j>=map->start_map_index)
		{
			map->only_map[i] = ft_strdup(line);
			i++;
		}
		j++;
		free(line);
	}
	map->only_map[i] = NULL;
	close(fd);
}

void add_zero_map(t_map *map)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(map->only_map[i])
    {
        j = 0;
        while(map->only_map[i][j])
        {
            if(map->only_map[i][j] == ' ')
            {
                map->only_map[i][j] = '0';
            }
            j++;
        }
        i++;
    }
}

void	check_params(t_map *map)
{
	if (map->NO_path == NULL || \
		map->SO_path == NULL || \
		map->WE_path == NULL || \
		map->EA_path == NULL || \
		map->c_rgb == NULL || \
		map->f_rgb == NULL)
	{
		set_error(map, "Incorrect parameters", MAP_ERROR);
	}
}
