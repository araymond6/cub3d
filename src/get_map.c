#include "../include/cub3D.h"

void print_map(char **map);

void read_map(t_map *map)
{
    int fd;
    int i;
    int j = 0;
    int reached_map = 0;
    char *line;

    i = 0;
    fd = open(map->map_path, O_RDONLY);
    map->only_map = malloc(sizeof(char *) * 1000);
    if (map->only_map == NULL)
    {
        perror("Memory allocation error");
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
   //print_map(map);
}

void print_map(char **map)
{
    printf("Printing map...\n");

    if (map == NULL) 
    {
        printf("map->only_map is NULL\n");
        return;
    }
    for (int i = 0; map[i] != NULL; i++)
    {
        printf("map %i : %s\n", i,  map[i]);
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

void algo_parsing(char **map, int x, int y, int map_height, int map_width) 
{
    if (x < 0 || y < 0 || x >= map_height || y >= map_width || map[x][y] != '0') {
        return;
    }

    map[x][y] = 'A';
    algo_parsing(map, x + 1, y, map_height, map_width);
    algo_parsing(map, x, y + 1, map_height, map_width);
    algo_parsing(map, x - 1, y, map_height, map_width);
    algo_parsing(map, x, y - 1, map_height, map_width);
}

void flood_fill(t_map *map, int x, int y) 
{
    char **duped_map = malloc((map->map_height + 1) * sizeof(char*));
    for (int i = 0; map->only_map[i] != NULL; i++) 
    {
        duped_map[i] = ft_strdup(map->only_map[i]);
        if (duped_map[i] == NULL) {
            printf("Memory allocation error in ft_strdup.\n");
            for (int j = 0; j < i; ++j) {
                free(duped_map[j]);
            }
            free(duped_map);
            return;
        }
    }
    duped_map[map->map_height] = NULL;

    print_map(duped_map);
    algo_parsing(duped_map, x, y, map->map_height, map->map_width);

    for (int i = 0; i < map->map_height; ++i) 
    {
        free(duped_map[i]);
    }
    free(duped_map);
}

