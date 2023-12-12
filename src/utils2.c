#include "../include/cub3D.h"

void	set_direction(t_cub *cub) //TODO: shorten when directions are okay
{
	if (cub->map.playerdir == 'N')
	{
		cub->v.playerdir[1] = 0;
		cub->v.playerdir[0] = -1;
		cub->v.camplane[0] = 0;
		cub->v.camplane[1] = 0.66;
	}
	else if (cub->map.playerdir == 'S')
	{
		
		cub->v.playerdir[1] = 0;
		cub->v.playerdir[0] = 1;
		cub->v.camplane[0] = 0;
		cub->v.camplane[1] = -0.66;
	}
	else if (cub->map.playerdir == 'E')
	{
		cub->v.playerdir[1] = 1;
		cub->v.playerdir[0] = 0;
		cub->v.camplane[0] = 0.66;
		cub->v.camplane[1] = 0;
	}
	else // if west
	{
		cub->v.playerdir[1] = -1;
		cub->v.playerdir[0] = 0;
		cub->v.camplane[0] = -0.66;
		cub->v.camplane[1] = 0;
	}
}

void	close_hook(void *param)
{
	t_cub	*cub;

	cub = NULL;
	if (param)
		cub = param;
	exit_program(cub);
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

	(void)x;
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

void	set_error(void *param, char *error_message, t_error error_type)
{
	t_cub	*cub;
	t_map	*map;

	(void)cub;
	(void)map;
	printf("Error\n%s\n", error_message);
	if (error_type == MAP_ERROR)
	{
		map = param;
		free_map(map);
	}
	else if (error_type == MLX_ERROR)
	{
		cub = param;
		free_all(cub);
	}
	exit(EXIT_FAILURE);
}
