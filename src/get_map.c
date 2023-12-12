#include "../include/cub3D.h"

void print_map(t_map *map);

void read_map(t_map *map)
{
	int fd;
	int i;
	int j = 0;
	map->only_map = NULL;
	char *line;

	i = 0;
	fd = open(map->map_path, O_RDONLY);
	map->only_map = malloc(sizeof(char *) * 100);
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

void print_map(t_map *map)
{
    printf("Printing map...\n");

    if (map->only_map == NULL) {
        printf("map->only_map is NULL\n");
        return;
    }
    for (int i = 0; map->only_map[i] != NULL; i++)
    {
        printf("map %i : %s\n", i,  map->only_map[i]);
    }
}
void free_map(t_map *map)
{
    for (int i = 0; map->only_map[i] != NULL; i++)
    {
        free(map->only_map[i]);
    }
    free(map->only_map);
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