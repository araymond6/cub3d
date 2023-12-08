#include "../include/cub.h"

void print_map(t_map *map);

void read_map(t_map *map)
{
    int fd;
    int i;
    int j = 0;
    map->only_map = NULL;
    int reached_map = 0;
    char *line;

    i = 0;
    fd = open(map->map_path, O_RDONLY);
    map->only_map = malloc(sizeof(char *) * 10000);
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
    map->only_map[i] = "\0";
    close(fd);
   //print_map(map);
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
