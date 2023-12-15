#include "../include/cub3D.h"

void findMapDimensions(t_map *map)
{
	int i = 0;
	int j = 0;

		while (map->only_map[i] != NULL) 
		{
			if ((int)ft_strlen(map->only_map[i]) >= j)
				j = (int)ft_strlen(map->only_map[i]);
			++i;
		}
		map->map_height = i;
		map->map_width = j;
}

void findPlayerPosition(t_map *map)
{
	int i = 0;
	int j = 0;
	char currentCell = map->only_map[i][j];
	int found;

	map->player_pos_x = 0;
	map->player_pos_y = 0;
	while (i <= map->map_height && map->only_map[i]) 
	{
		j = 0;
		while (j < map->map_width && map->only_map[i][j]) 
		{
			currentCell = map->only_map[i][j];
			if (currentCell == 'N' || currentCell == 'E' || \
				currentCell == 'S' || currentCell == 'W')
			{
				if (found == 1)
					set_error(map, "Multiple player positions found", MAP_ERROR);
				map->playerdir = currentCell;
				map->only_map[i][j] = '0';
				map->player_pos_x = i;
				map->player_pos_y = j;
				found = 1;
			}
			++j;
		}
		++i;
	}
	if (found != 1)
		set_error(map, "No player position found", MAP_ERROR);
}

void wrong_character_in_map(t_map *map)
{
	int i;
	int j;

	i = 0;
	while(map->only_map[i])
	{
		j = 0;
		while(map->only_map[i][j])
		{
			if(map->only_map[i][j] != '1' && map->only_map[i][j] != '0' && map->only_map[i][j] != ' ' && map->only_map[i][j] != 'W' &&
				map->only_map[i][j] != 'E' && map->only_map[i][j] != 'S' && map->only_map[i][j] != 'N' && map->only_map[i][j] != '\n')
					set_error(map, "Invalid character in the map", MAP_ERROR);
			j++;
		}
		i++;
	}
}