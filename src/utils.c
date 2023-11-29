#include "../include/cub3D.h"

int	getColor(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	freeArray(char **arr)
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