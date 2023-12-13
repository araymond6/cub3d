#include "../include/cub3D.h"

int	parse_rgb_values(const char *rgbString, t_map *map, int isFloor)
{
	char	*token;
	char	*copy;
	int		count;
	int *color[3]; // red/green/blue

	copy = ft_strdup(rgbString);
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