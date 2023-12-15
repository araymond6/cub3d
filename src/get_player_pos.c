/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 12:14:59 by dwawzyni          #+#    #+#             */
/*   Updated: 2023/12/15 14:30:58 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	set_player_position(t_map *map, int i, int j, char currentcell);

void	find_map_dimensions(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->only_map[i] != NULL)
	{
		if ((int)ft_strlen(map->only_map[i]) >= j)
			j = (int)ft_strlen(map->only_map[i]);
		++i;
	}
	map->map_height = i;
	map->map_width = j;
}

void	find_player_position(t_map *map)
{
	int		i;
	int		j;
	char	current_cell;
	int		found;

	i = -1;
	while (i <= map->map_height && map->only_map[++i])
	{
		j = -1;
		while (++j < map->map_width && map->only_map[i][j])
		{
			current_cell = map->only_map[i][j];
			if (current_cell == 'N' || current_cell == 'E' || \
				current_cell == 'S' || current_cell == 'W')
			{
				if (found == 1)
					set_error(map, "Multiple player positions found",
						MAP_ERROR);
				set_player_position(map, i, j, current_cell);
				found = 1;
			}
		}
	}
	if (found != 1)
		set_error(map, "No player position found", MAP_ERROR);
}

void	wrong_character_in_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->only_map[i])
	{
		j = 0;
		while (map->only_map[i][j])
		{
			if (map->only_map[i][j] != '1' && map->only_map[i][j] != '0'
				&& map->only_map[i][j] != ' ' && map->only_map[i][j] != 'W' &&
				map->only_map[i][j] != 'E' && map->only_map[i][j] != 'S'
					&& map->only_map[i][j] != 'N'
					&& map->only_map[i][j] != '\n')
				set_error(map, "Invalid map", MAP_ERROR);
			j++;
		}
		i++;
	}
}

void	set_player_position(t_map *map, int i, int j, char currentcell)
{
	map->playerdir = currentcell;
	map->only_map[i][j] = '0';
	map->player_pos_x = i;
	map->player_pos_y = j;
}
