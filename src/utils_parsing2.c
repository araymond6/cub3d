/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:20:16 by dwawzyni          #+#    #+#             */
/*   Updated: 2023/12/15 14:23:18 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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

void	get_color_path_by_token(t_map *s_map, char *token)
{
	static int	count[2] = {0, 0};

	if (ft_strcmp(token, "F") == 0)
	{
		count[0]++;
		check_count(s_map, count[0]);
		s_map->f_rgb = ft_strtok(NULL, " ");
	}
	if (ft_strcmp(token, "C") == 0)
	{
		count[1]++;
		check_count(s_map, count[1]);
		s_map->c_rgb = ft_strtok(NULL, " ");
	}
}
