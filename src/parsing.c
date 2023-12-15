/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:55:46 by dwawzyni          #+#    #+#             */
/*   Updated: 2023/12/15 14:23:06 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	check_map_args(t_map *s_map)
{
	int	fd;
	int	lines_nb;
	int	i;
	int	file_size;

	lines_nb = 0;
	i = 0;
	fd = open(s_map->map_path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nUnable to open %s\n", s_map->map_path);
		exit(EXIT_FAILURE);
	}
	file_size = count_file_size(fd);
	s_map->map = malloc(sizeof(char *) * (file_size + 1));
	malloc_error_map(s_map, fd);
	close(fd);
	fd = open(s_map->map_path, O_RDONLY);
	s_map->map[i] = get_next_line(fd);
	while (s_map->map[i] && i < file_size)
	{
		s_map->map[++i] = get_next_line(fd);
		lines_nb++;
	}
	close(fd);
}

void	get_texture_path(t_map *s_map)
{
	int		i;
	char	*token;

	i = -1;
	while (s_map->map[++i])
	{
		token = (ft_strtok(trim_spaces(s_map->map[i]), " "));
		while (token != NULL)
		{
			if (ft_strcmp(token, "NO") == 0 || ft_strcmp(token, "SO") == 0
				|| ft_strcmp(token, "WE") == 0 || ft_strcmp(token, "EA") == 0)
				set_texture_path(get_texture_path_by_token(s_map, token),
					ft_strtok(NULL, " "), s_map);
			else if (ft_strcmp(token, "F") == 0 || ft_strcmp(token, "C") == 0)
				get_color_path_by_token(s_map, token);
			else if (check_all_params_exist(s_map)
				&& s_map->start_map_index == 0)
				s_map->start_map_index = i;
			token = ft_strtok(NULL, " ");
		}
	}
	check_params(s_map);
}

char	**get_texture_path_by_token(t_map *s_map, char *token)
{
	static int	count[4] = {0, 0, 0, 0};

	if (ft_strcmp(token, "NO") == 0)
	{
		count[0]++;
		return (check_count(s_map, count[0]), &s_map->no_path);
	}
	if (ft_strcmp(token, "SO") == 0)
	{
		count[1]++;
		return (check_count(s_map, count[1]), &s_map->so_path);
	}
	if (ft_strcmp(token, "WE") == 0)
	{
		count[2]++;
		return (check_count(s_map, count[2]), &s_map->we_path);
	}
	if (ft_strcmp(token, "EA") == 0)
	{
		count[3]++;
		return (check_count(s_map, count[3]), &s_map->ea_path);
	}
	return (NULL);
}

int	check_all_params_exist(t_map *s_map)
{
	return (s_map->c_rgb != NULL && s_map->f_rgb != NULL
		&& s_map->no_path != NULL && \
		s_map->so_path != NULL && s_map->we_path != NULL
		&& s_map->ea_path != NULL);
}

char	*trim_texture_path(t_map *s_map, char *texture_path)
{
	int		i;
	int		j;
	char	*clean_path;

	i = 0;
	j = 0;
	if (!(texture_path))
		set_error(s_map, "test error", MAP_ERROR);
	clean_path = malloc(ft_strlen(texture_path) - i + 1);
	if (clean_path == NULL)
	{
		set_error(s_map, "Memory allocation error", MAP_ERROR);
	}
	while (texture_path[i])
	{
		clean_path[j] = texture_path[i];
		i++;
		j++;
	}
	clean_path[j] = '\0';
	return (clean_path);
}
