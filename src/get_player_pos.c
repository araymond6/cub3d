#include "../include/cub.h"


void findMapDimensions(t_map *map) 
{
    int i = 0;
    int j = 0;

     while (map->only_map[i][0] != '\0') 
     {
        if(ft_strlen(map->only_map[i]) >= j)
            j = ft_strlen(map->only_map[i]);
         ++i;
     }
     map->map_height = i-1;
     map->map_width = j;
}

void findPlayerPosition(t_map *map) 
{
    int i = 0;
    int j = 0;
    char currentCell = map->only_map[i][j];
    map->player_pos_x = 0;
    map->player_pos_y = 0;
    while (i <= map->map_height) 
    {
        j = 0;
        while (j < map->map_width) {
            currentCell = map->only_map[i][j];
            if (currentCell == 'N' || currentCell == 'E' || currentCell == 'S' || currentCell == 'W')
            {
                map->player_pos_x = i;
                map->player_pos_y = j;
                return;
            }
            ++j;
        }
        ++i;
    }
}