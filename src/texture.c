#include "../include/cub3D.h"

void	fill_array(mlx_texture_t *texture, int **array)
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
			array[y][x] = get_color((uint32_t)texture->pixels[i],
					(uint32_t)texture->pixels[i + 1],
					(uint32_t)texture->pixels[i + 2],
					(uint32_t)texture->pixels[i + 3]);
			i += 4;
			x++;
		}
		y++;
	}
}

int	**texture_to_array(mlx_texture_t *texture)
{
	int	i;
	int	**array;

	i = 0;
	array = ft_calloc(texture->height + 1, sizeof(int *));
	if (!array)
		return (NULL);
	while (i < texture->height)
	{
		array[i] = ft_calloc(texture->width, sizeof(int));
		if (!array[i])
		{
			free_int_array(array, MAPWIDTH, MAPHEIGHT);
			return (NULL);
		}
		i++;
	}
	fill_array(texture, array);
	return (array);
}

void	free_texture(t_cub *cub)
{
	if (cub->texture.northarr)
		free_int_array(cub->texture.northarr, MAPWIDTH, MAPHEIGHT);
	if (cub->texture.southarr)
		free_int_array(cub->texture.southarr, MAPWIDTH, MAPHEIGHT);
	if (cub->texture.westarr)
		free_int_array(cub->texture.westarr, MAPWIDTH, MAPHEIGHT);
	if (cub->texture.eastarr)
		free_int_array(cub->texture.eastarr, MAPWIDTH, MAPHEIGHT);
	if (cub->texture.north)
		mlx_delete_texture(cub->texture.north);
	if (cub->texture.south)
		mlx_delete_texture(cub->texture.south);
	if (cub->texture.west)
		mlx_delete_texture(cub->texture.west);
	if (cub->texture.east)
		mlx_delete_texture(cub->texture.east);
}

void	init_texture(t_cub *cub)
{
	cub->texture.north = mlx_load_png("textures/Birch.png");
	cub->texture.south = mlx_load_png("textures/Jungle.png");
	cub->texture.west = mlx_load_png("textures/Oak.png");
	cub->texture.east = mlx_load_png("textures/Spruce.png");
	if (!cub->texture.north || !cub->texture.south || !cub->texture.west \
		|| !cub->texture.east)
	{
		free_texture(cub);
		exit_program(cub);
	}
	
	cub->texture.northarr = texture_to_array(cub->texture.north);
	cub->texture.southarr = texture_to_array(cub->texture.south);
	cub->texture.westarr = texture_to_array(cub->texture.west);
	cub->texture.eastarr = texture_to_array(cub->texture.east);
	if (!cub->texture.northarr || !cub->texture.southarr \
		|| !cub->texture.westarr || !cub->texture.eastarr)
	{
		free_texture(cub);
		exit_program(cub);
	}
}