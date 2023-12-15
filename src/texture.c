/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:45:25 by araymond          #+#    #+#             */
/*   Updated: 2023/12/15 11:45:26 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	**texture_to_array(t_cub *cub, mlx_texture_t *texture)
{
	uint32_t	i;
	int			**array;

	i = 0;
	array = ft_calloc(texture->height, sizeof(int *));
	if (!array)
		return (NULL);
	while (i < texture->height)
	{
		array[i] = ft_calloc(texture->width, sizeof(int));
		if (!array[i])
		{
			free_int_array(array, cub->map.map_width, cub->map.map_width);
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
		free_int_array(cub->texture.northarr, cub->texture.north->width, \
		cub->texture.north->height);
	if (cub->texture.southarr)
		free_int_array(cub->texture.southarr, cub->texture.south->width, \
		cub->texture.south->height);
	if (cub->texture.westarr)
		free_int_array(cub->texture.westarr, cub->texture.west->width, \
		cub->texture.west->height);
	if (cub->texture.eastarr)
		free_int_array(cub->texture.eastarr, cub->texture.east->width, \
		cub->texture.east->height);
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
	cub->texture.north = mlx_load_png(cub->map.no_path);
	cub->texture.south = mlx_load_png(cub->map.so_path);
	cub->texture.west = mlx_load_png(cub->map.we_path);
	cub->texture.east = mlx_load_png(cub->map.ea_path);
	if (!cub->texture.north || !cub->texture.south || !cub->texture.west \
		|| !cub->texture.east)
	{
		set_error(cub, "Failed to load PNG", MLX_ERROR);
	}
	cub->texture.northarr = texture_to_array(cub, cub->texture.north);
	cub->texture.southarr = texture_to_array(cub, cub->texture.south);
	cub->texture.westarr = texture_to_array(cub, cub->texture.west);
	cub->texture.eastarr = texture_to_array(cub, cub->texture.east);
	if (!cub->texture.northarr || !cub->texture.southarr \
		|| !cub->texture.westarr || !cub->texture.eastarr)
	{
		set_error(cub, "Memory allocation error", MLX_ERROR);
	}
}
