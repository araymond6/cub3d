/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:20:16 by dwawzyni          #+#    #+#             */
/*   Updated: 2023/12/15 12:50:47 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	set_paths(t_map *s_map, char *token, int i)
{
	if (ft_strcmp(token, "NO") == 0)
		set_texture_path(&s_map->no_path, ft_strtok(NULL, " "), s_map);
	else if (ft_strcmp(token, "SO") == 0)
		set_texture_path(&s_map->so_path, ft_strtok(NULL, " "), s_map);
	else if (ft_strcmp(token, "WE") == 0)
		set_texture_path(&s_map->we_path, ft_strtok(NULL, " "), s_map);
	else if (ft_strcmp(token, "EA") == 0)
		set_texture_path(&s_map->ea_path, ft_strtok(NULL, " "), s_map);
	else if (ft_strcmp(token, "F") == 0)
		s_map->f_rgb = (ft_strtok(NULL, " "));
	else if (ft_strcmp(token, "C") == 0)
		s_map->c_rgb = (ft_strtok(NULL, " "));
	else if (s_map->c_rgb != NULL && s_map->f_rgb != NULL && \
				s_map->no_path != NULL && s_map->so_path != NULL && \
				s_map->we_path != NULL && s_map->ea_path != NULL && \
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

char	*trim_spaces(char *str)
{
	char	*end;

	while (ft_isspace(*str))
	{
		str++;
	}
	end = str + ft_strlen(str) - 1;
	while (end > str && ft_isspace(*end))
	{
		end--;
	}
	*(end + 1) = '\0';
	return (str);
}

void	set_texture_path(char **dest, char *token, t_map *s_map)
{
	free(*dest);
	*dest = trim_texture_path(s_map, token);
	if (*dest == NULL)
	{
		set_error(s_map, "Unable to get path", MAP_ERROR);
	}
}
