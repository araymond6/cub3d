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

void algo_parsing(t_map *map, char **only_map, int x, int y) 
{
	if (x < 0 || y < 0 || x >= map->map_height || y >= map->map_width || only_map[x][y] != '0') {
		return;
	}
	only_map[x][y] = 'A';
	if(only_map[x][y+1] == '\n' || x == 0 || y == 0 || x == map->map_height-1)
	{
		free_char_array(only_map);
		set_error(map, "Map is not closed", MAP_ERROR);
	}
	else if(only_map[x-1][y]== ' ' || only_map[x+1][y] == ' ' || only_map[x][y-1] == ' ' || only_map[x][y+1] == ' ')
	{
		free_char_array(only_map);
		set_error(map, "Map is not closed 2", MAP_ERROR);
	}
	algo_parsing(map, only_map, x + 1, y);
	algo_parsing(map, only_map, x, y + 1);
	algo_parsing(map, only_map, x - 1, y);
	algo_parsing(map, only_map, x, y - 1);
}

void flood_fill(t_map *map, int x, int y) 
{
    char **duped_map = malloc((map->map_height + 1) * sizeof(char*));
    
    for (int i = 0; i < map->map_height; i++) 
    {
        // Allocate memory for each row including extra '0' characters
        duped_map[i] = malloc((map->map_width + 1) * sizeof(char));

        if (duped_map[i] == NULL) 
        {
            printf("Memory allocation error in row %d.\n", i);
            for (int j = 0; j < i; ++j) {
                free(duped_map[j]);
            }
            free(duped_map);
            return;
        }

        int len = strlen(map->only_map[i]);
        for (int j = 0; j < map->map_width; j++) 
        {
            if (j < len) 
            {
                if (map->only_map[i][j] != '\n') {
                    duped_map[i][j] = map->only_map[i][j];
                } else {
                    // Replace '\n' with '0'
                    duped_map[i][j] = '0';
                }
            } 
            else 
            {
                duped_map[i][j] = '0';
            }
        }

        // Null-terminate the row
        duped_map[i][map->map_width] = '\0';
    }
    
    // Null-terminate the array
    duped_map[map->map_height] = NULL;

    algo_parsing(map, duped_map, x, y);

    // Free allocated memory
    for (int i = 0; i < map->map_height; ++i) 
    {
        free(duped_map[i]);
    }
    free(duped_map);
}