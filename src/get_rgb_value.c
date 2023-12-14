#include "../include/cub3D.h"

int	parse_rgb_values(const char *rgbString, t_map *map, int isFloor)
{
	char	*token;
	char	*copy;
	int		count;
	char **check_if_number;
	int j = 0;
	int *color[3]; // red/green/blue

	copy = ft_strdup(rgbString);
	check_if_number = ft_split(rgbString,',');
	count = 0;
	while(check_if_number[count] != NULL)
	{
		j = 0;
		while(check_if_number[count][j])
		{
			if(!(ft_isdigit(check_if_number[count][j])))
				set_error(map,"one character is not a digit",MAP_ERROR);
			j++;
		}
		count++;
	}
	if (!copy)
		set_error(map, "Memory allocation error", MAP_ERROR);
	count = 0;
	token = ft_strtok(copy, ",");
	while (token != NULL && count < 3)
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

void check_rgb_values(t_map *map)
{
	int i = 0;
	int count = 0;
	if(parse_rgb_values(map->f_rgb, map, 1) < 3 || parse_rgb_values(map->c_rgb, map, 0) < 3)
		set_error(map,"error in rgb value",MAP_ERROR);
	if(map->c_red > 255 || map->c_green > 255 || map->c_blue > 255 || map->c_red<0 || map->c_green<0 || map->c_blue<0)
		set_error(map,"Ceiling value outside of range (0-255)",MAP_ERROR);
	if(map->f_red > 255 || map->f_green > 255 || map->f_blue > 255 || map->f_red<0 || map->f_green<0 || map->f_blue<0)
		set_error(map,"Floor value outside of range (0-255)",MAP_ERROR);
	while(map->c_rgb[i])
	{
		if(map->c_rgb[i] == ',')
			count++;
		i++;
	}
	if(count > 2)
		set_error(map,"test error",MAP_ERROR);

}