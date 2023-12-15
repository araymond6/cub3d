/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwawzyni <dwawzyni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:20:16 by dwawzyni          #+#    #+#             */
/*   Updated: 2023/12/15 11:22:00 by dwawzyni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		s_map->f_rgb = (ft_strtok(NULL, " "));
	else if (ft_strcmp(token, "C") == 0)
		s_map->c_rgb = (ft_strtok(NULL, " "));
	else if (s_map->c_rgb != NULL && s_map->f_rgb != NULL && \
				s_map->NO_path != NULL && s_map->SO_path != NULL && \
				s_map->WE_path != NULL && s_map->EA_path != NULL && \
				s_map->start_map_index == 0)
		s_map->start_map_index = i;
	token = ft_strtok(NULL, " ");
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
