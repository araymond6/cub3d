#include "../include/cub3D.h"

int	get_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	free_char_array(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i] != NULL)
		{
			if (arr[i])
				free(arr[i]);
			i++;
		}
		free(arr);
	}
}

void	free_int_array(int **arr, int x, int y)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (i < y)
		{
			if (arr[i])
				free(arr[i]);
			i++;
		}
		free(arr);
	}
}

void	exit_program(t_cub *cub)
{
	exit(0);
}

//TODO: REMOVE THIS WHEN PARSING DONE
void	fill_map(t_cub *cub)
{
	int	i;
	int	j;

	cub->map.map = ft_calloc(cub->map.map_height + 1, sizeof(char *));
	i = 0;
	while (i < cub->map.map_height)
	{
		j = 0;
		cub->map.map[i] = ft_calloc(cub->map.map_width + 1, sizeof(char));
		while (j < cub->map.map_width)
		{
			if (j == 0 || j == cub->map.map_width - 1 || i  == 0 || i == cub->map.map_height - 1)
				cub->map.map[i][j] = '1';
			else
				cub->map.map[i][j] = '0';
			j++;
		}
		i++;
	}
}