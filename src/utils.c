/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwawzyni <dwawzyni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:45:11 by dwawzyni          #+#    #+#             */
/*   Updated: 2023/12/15 11:45:12 by dwawzyni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	free_all(t_cub *cub);

void	init_cub(t_cub *cub)
{
	cub->v.pos[0] = (double)cub->map.player_pos_x + 0.5;
	cub->v.pos[1] = (double)cub->map.player_pos_y + 0.5;
	cub->v.step[0] = 1;
	cub->v.step[1] = 1;
	cub->v.camangle = 0.5;
	cub->v.movespeed = 0.00007;
	cub->v.rotspeed = 0.00005;
	set_direction(cub);
	free_char_array(cub->map.map);
	cub->map.map = cub->map.only_map;
	cub->ceiling = get_color(cub->map.c_red, cub->map.c_green, \
	cub->map.c_blue, 255);
	cub->floor = get_color(cub->map.f_red, cub->map.f_green, \
	cub->map.f_blue, 255);
}

void	exit_program(t_cub *cub)
{
	if (cub)
	{
		free_all(cub);
	}
	exit(EXIT_SUCCESS);
}

void	free_all(t_cub *cub)
{
	free_texture(cub);
	if (cub->map.map)
		free_map(&cub->map);
	if (cub->img)
		mlx_delete_image(cub->mlx, cub->img);
	if (cub->mlx)
	{
		mlx_close_window(cub->mlx);
		mlx_terminate(cub->mlx);
	}
	if (cub->map.no_path)
		free(cub->map.no_path);
	if (cub->map.so_path)
		free(cub->map.so_path);
	if (cub->map.we_path)
		free(cub->map.we_path);
	if (cub->map.ea_path)
		free(cub->map.ea_path);
}

int	get_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	check_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		return (-1);
	}
	close(fd);
	return (0);
}
