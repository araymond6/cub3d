#include "../include/cub3D.h"

void	set_paths(t_map *map, char *token, int i)
{
	if (ft_strcmp(token, "NO") == 0)
			set_texture_path(&map->NO_path, ft_strtok(NULL, " "), map);
		else if (ft_strcmp(token, "SO") == 0)
			set_texture_path(&map->SO_path, ft_strtok(NULL, " "), map);
		else if (ft_strcmp(token, "WE") == 0)
			set_texture_path(&map->WE_path, ft_strtok(NULL, " "), map);
		else if (ft_strcmp(token, "EA") == 0)
			set_texture_path(&map->EA_path, ft_strtok(NULL, " "), map);
		else if(ft_strcmp(token,"F") == 0)
			map->f_rgb = (ft_strtok(NULL," "));
		else if(ft_strcmp(token,"C") == 0)
			map->c_rgb = (ft_strtok(NULL," "));
		else if(map->c_rgb != NULL && map->f_rgb != NULL && map->NO_path != NULL && map->SO_path != NULL 
			&& map->WE_path != NULL && map->EA_path != NULL && map->start_map_index == 0)
				map->start_map_index = i;
		token = ft_strtok(NULL, " ");
}