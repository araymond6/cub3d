#include "../include/cub3D.h"

void	set_paths(t_map *s_map, char *token, int i)
{
	if (ft_strcmp(token, "NO") == 0)
		set_texture_path(&s_map->NO_path, ft_strtok(NULL, " "), s_map);
	else if (ft_strcmp(token, "SO") == 0)
		set_texture_path(&s_map->SO_path, ft_strtok(NULL, " "), s_map);
	else if (ft_strcmp(token, "WE") == 0)
		set_texture_path(&s_map->WE_path, ft_strtok(NULL, " "), s_map);
	else if (ft_strcmp(token, "EA") == 0)
		set_texture_path(&s_map->EA_path, ft_strtok(NULL, " "), s_map);
	else if (ft_strcmp(token, "F") == 0)
		s_map->f_rgb = (ft_strtok(NULL," "));
	else if (ft_strcmp(token, "C") == 0)
		s_map->c_rgb = (ft_strtok(NULL," "));
	else if (s_map->c_rgb != NULL && s_map->f_rgb != NULL && \
			s_map->NO_path != NULL && s_map->SO_path != NULL && \
			s_map->WE_path != NULL && s_map->EA_path != NULL && \
			s_map->start_map_index == 0)
		s_map->start_map_index = i;
	token = ft_strtok(NULL, " ");
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