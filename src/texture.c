#include "../include/cub3D.h"

void	fillArray(mlx_texture_t *texture, int **array)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	i;

	i = 0;
	y = 0;
	while (y < texture->height - 1)
	{
		x = 0;
		while (x < texture->width)
		{
			array[y][x] = ft_color((uint32_t)texture->pixels[i],
					(uint32_t)texture->pixels[i + 1],
					(uint32_t)texture->pixels[i + 2],
					(uint32_t)texture->pixels[i + 3]);
			i += 4;
			x++;
		}
		y++;
	}
}

int	**textureToArray(mlx_texture_t *texture)
{
	int	i;
	int	**array;

	i = 0;
	array = ft_calloc(texture->height + 1, sizeof(int));
	if (!array)
		return (NULL);
	while (i < texture->height)
	{
		array[i] = ft_calloc(texture->width, sizeof(int));
		if (!array[i])
		{
			freeArray(array);
			return (NULL);
		}
		i++;
	}
	fillArray(texture, array);
	return (array);
}

void	freeTexture(t_cub *cub)
{
	if (cub->texture.northArr)
		freeArray(cub->texture.northArr); // prob not the right func, make new one
	if (cub->texture.southArr)
		freeArray(cub->texture.southArr);
	if (cub->texture.westArr)
		freeArray(cub->texture.westArr);
	if (cub->texture.eastArr)
		freeArray(cub->texture.eastArr);
	if (cub->texture.north)
		mlx_delete_texture(cub->texture.north);
	if (cub->texture.south)
		mlx_delete_texture(cub->texture.south);
	if (cub->texture.west)
		mlx_delete_texture(cub->texture.west);
	if (cub->texture.east)
		mlx_delete_texture(cub->texture.east);
}

void	initTexture(t_cub *cub)
{
	cub->texture.north = mlx_load_png("../textures/Birch.png");
	cub->texture.south = mlx_load_png("../textures/Jungle.png");
	cub->texture.west = mlx_load_png("../textures/Oak.png");
	cub->texture.east = mlx_load_png("../textures/Spruce.png");
	if (!cub->texture.north || cub->texture.south || cub->texture.west \
		|| cub->texture.east)
	{
		freeTexture(cub);
		exitProgram(cub);
	}
	
	cub->texture.northArr = textureToArray(cub->texture.north);
	cub->texture.southArr = textureToArray(cub->texture.south);
	cub->texture.westArr = textureToArray(cub->texture.west);
	cub->texture.eastArr = textureToArray(cub->texture.east);
	if (!cub->texture.northArr || !cub->texture.southArr \
		|| !cub->texture.westArr || !cub->texture.eastArr)
	{
		freeTexture(cub);
		exitProgram(cub);
	}
}