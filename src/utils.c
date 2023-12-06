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
		while (arr[i] != NULL)
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
	mlx_close_window(cub->mlx);
}

void	close_hook(void *param)
{
	t_cub	*cub;

	if (param)
		cub = param;
	mlx_close_window(cub->mlx);
}

//TODO: REMOVE THIS WHEN PARSING DONE
void	fill_map(t_cub *cub)
{
	int	i;
	int	j;

	cub->map.map = ft_calloc(MAPHEIGHT + 1, sizeof(char *));
	i = 0;
	while (i < MAPHEIGHT)
	{
		j = 0;
		cub->map.map[i] = ft_calloc(MAPWIDTH + 1, sizeof(char));
		while (j < MAPWIDTH)
		{
			if (j == 0 || j == MAPWIDTH - 1 || i  == 0 || i == MAPHEIGHT - 1)
				cub->map.map[i][j] = '1';
			else
				cub->map.map[i][j] = '0';
			j++;
		}
		i++;
	}
}