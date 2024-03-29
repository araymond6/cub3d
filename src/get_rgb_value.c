/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgb_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 12:12:14 by dwawzyni          #+#    #+#             */
/*   Updated: 2023/12/19 11:05:52 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	verif_number(t_map *map, const char *rgbString);
void	set_rgb_color(t_map *map, int isFloor, int *color[3]);

int	parse_rgb_values(const char *rgbString, t_map *map, int isFloor)
{
	char	*token;
	char	*copy;
	int		count;
	int		*color[3];

	count = 0;
	copy = ft_strdup(rgbString);
	if (!copy)
		set_error(map, "Memory allocation error", MAP_ERROR);
	verif_number(map, rgbString);
	token = ft_strtok(copy, ",");
	while (token != NULL && count < 3)
	{
		set_rgb_color(map, isFloor, color);
		if (count == 0)
			*color[0] = ft_atoi(token);
		else if (count == 1)
			*color[1] = ft_atoi(token);
		else if (count == 2)
			*color[2] = ft_atoi(token);
		token = ft_strtok(NULL, ",");
		count++;
	}
	free(copy);
	return (count);
}

void	check_rgb_values(t_map *map)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (parse_rgb_values(map->f_rgb, map, 1) < 3 || parse_rgb_values(map->c_rgb,
			map, 0) < 3)
		set_error(map, "Error in RGB value", MAP_ERROR);
	if (map->c_red > 255 || map->c_green > 255 || map->c_blue > 255
		|| map->c_red < 0 || map->c_green < 0 || map->c_blue < 0)
		set_error(map, "Ceiling value outside of range (0-255)", MAP_ERROR);
	if (map->f_red > 255 || map->f_green > 255 || map->f_blue > 255
		|| map->f_red < 0 || map->f_green < 0 || map->f_blue < 0)
		set_error(map, "Floor value outside of range (0-255)", MAP_ERROR);
	while (map->c_rgb[i])
	{
		if (map->c_rgb[i] == ',')
			count++;
		i++;
	}
	if (count > 2)
		set_error(map, "Error in RGB value", MAP_ERROR);
}

void	verif_number(t_map *map, const char *rgbString)
{
	int		count;
	int		j;
	char	**check_if_number;

	check_if_number = ft_split(rgbString, ',');
	if (!check_if_number)
		set_error(map, "Memory allocation error", MAP_ERROR);
	j = 0;
	count = 0;
	while (check_if_number[count] != NULL)
	{
		j = 0;
		while (check_if_number[count][j])
		{
			if (!(ft_isdigit(check_if_number[count][j])))
			{
				free_char_array(check_if_number);
				set_error(map, "one character is not a digit", MAP_ERROR);
			}
			j++;
		}
		count++;
	}
	free_char_array(check_if_number);
}

void	set_rgb_color(t_map *map, int isFloor, int *color[3])
{
	if (isFloor)
	{
		color[0] = &map->f_red;
		color[1] = &map->f_green;
		color[2] = &map->f_blue;
	}
	else
	{
		color[0] = &map->c_red;
		color[1] = &map->c_green;
		color[2] = &map->c_blue;
	}
}

void	flood_fill_part(t_map *map, char **duped_map, int i, int j)
{
	int	len;

	len = ft_strlen(map->only_map[i]);
	while (j < map->map_width)
	{
		if (j < len)
		{
			if (map->only_map[i][j] != '\n')
				duped_map[i][j] = map->only_map[i][j];
			else
				duped_map[i][j] = '0';
		}
		else
			duped_map[i][j] = '0';
		j++;
	}
}
