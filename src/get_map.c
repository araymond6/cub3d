/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 12:19:47 by dwawzyni          #+#    #+#             */
/*   Updated: 2023/12/19 10:29:59 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	read_map(t_map *map, int fd, int i, int j)
{
	char	*line;

	close_and_open(map, &fd);
	if (count_map_size(map, fd) > 205)
		set_error(map, "Map is too big", MAP_ERROR);
	close_and_open(map, &fd);
	map->only_map = ft_calloc(sizeof(char *), (count_map_size(map, fd) + 1));
	if (!map->only_map)
		set_error(map, "Memory allocation error", MAP_ERROR);
	close_and_open(map, &fd);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strlen(line) > 205)
			set_error(map, "Map is too long", MAP_ERROR);
		if (j >= map->start_map_index)
			map->only_map[i++] = ft_strdup(line);
		j++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	add_zero_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->only_map[i])
	{
		j = 0;
		while (map->only_map[i][j])
		{
			if (map->only_map[i][j] == ' ')
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
	if (map->no_path == NULL || 
		map->so_path == NULL || 
		map->we_path == NULL || 
		map->ea_path == NULL || 
		map->c_rgb == NULL || 
		map->f_rgb == NULL)
	{
		set_error(map, "Incorrect parameters", MAP_ERROR);
	}
}

void	algo_parsing(t_map *map, char **only_map, int x, int y)
{
	if (x < 0 || y < 0 || x >= map->map_height || y >= map->map_width
		|| only_map[x][y] != '0')
	{
		return ;
	}
	only_map[x][y] = 'A';
	if (only_map[x][y + 1] == '\n' || x == 0 || y == 0 || x == map->map_height
		- 1)
	{
		free_char_array(only_map);
		set_error(map, "Map is not closed", MAP_ERROR);
	}
	algo_parsing(map, only_map, x + 1, y);
	algo_parsing(map, only_map, x, y + 1);
	algo_parsing(map, only_map, x - 1, y);
	algo_parsing(map, only_map, x, y - 1);
}

void	flood_fill(t_map *map, int x, int y)
{
	char	**duped_map;
	int		i;
	int		j;

	i = 0;
	duped_map = ft_calloc((map->map_height + 1), sizeof(char *));
	while (i < map->map_height)
	{
		j = 0;
		duped_map[i] = malloc((map->map_width + 1) * sizeof(char));
		if (duped_map[i] == NULL)
		{
			free_char_array(duped_map);
			set_error(map, "Memory allocation error", MAP_ERROR);
		}
		flood_fill_part(map, duped_map, i, j);
		duped_map[i][map->map_width] = '\0';
		i++;
	}
	duped_map[map->map_height] = NULL;
	algo_parsing(map, duped_map, x, y);
	free_char_array(duped_map);
}
