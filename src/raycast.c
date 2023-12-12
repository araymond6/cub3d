#include "../include/cub3D.h"

// calculates the intersection point of a ray with a wall and uses it
// to place the appripriate texture coordinate
void	find_hit(t_cub *cub, mlx_texture_t *texture)
{
	cub->v.hit = 0;
	if (cub->v.side == 0 || cub->v.side == 1)
	{
		cub->v.hit = cub->v.pos[1] + cub->v.perpwalldist * \
		cub->v.raydir[1];
	}
	else
	{
		cub->v.hit = cub->v.pos[0] + cub->v.perpwalldist * \
		cub->v.raydir[0];
	}
	cub->v.hit -= (int)cub->v.hit;
	cub->v.texture = (int)(cub->v.hit * (double)texture->width);
	if ((cub->v.side == 0 || cub->v.side == 1) && cub->v.raydir[0] > 0)
		cub->v.texture = texture->width - cub->v.texture - 1;
	if ((cub->v.side == 2 || cub->v.side == 3) && cub->v.raydir[1] < 0)
		cub->v.texture = texture->width - cub->v.texture - 1;
}

// draws the line for the wall with the correct texture point, 
void	draw_line(t_cub *cub, mlx_texture_t *texture, int **ar, int x)
{
	double	dist;
	double	pos;
	int		tex_y;
	int		j;

	dist = 1.0 * texture->height / cub->v.lineheight;
	pos = ((double)cub->v.drawpoints[0] - (double)SCREENHEIGHT / 2
			+ (double) cub->v.lineheight / 2) * dist;
	if (pos < 0)
		pos = 0;
	j = cub->v.drawpoints[0] - 1;
	while (++j < cub->v.drawpoints[1])
	{
		tex_y = (int)pos;
		if (pos > texture->height - 1)
			pos = texture->height - 1;
		pos += dist;
		mlx_put_pixel(cub->img, x, j, ar[tex_y][cub->v.texture]);
	}
}

// selects the correct texture to draw depending on the wall side it's hitting
void	select_texture(t_cub *cub, int x)
{
	if (cub->v.side == 0)
	{
		find_hit(cub, cub->texture.south);
		draw_line(cub, cub->texture.south, cub->texture.southarr, x);
	}
	if (cub->v.side == 1)
	{
		find_hit(cub, cub->texture.north);
		draw_line(cub, cub->texture.north, cub->texture.northarr, x);
	}
	if (cub->v.side == 2)
	{
		find_hit(cub, cub->texture.east);
		draw_line(cub, cub->texture.east, cub->texture.eastarr, x);
	}
	if (cub->v.side == 3)
	{
		find_hit(cub, cub->texture.west);
		draw_line(cub, cub->texture.west, cub->texture.westarr, x);
	}
}

// draws under the wall, and behind/over the wall with the appropriate color
void	draw_floornwalls(t_cub *cub, int x)
{
	int	y;

	y = 0;
	while (y < cub->v.drawpoints[0])
		mlx_put_pixel(cub->img, x, y++, cub->ceiling);
	while (y < SCREENHEIGHT)
		mlx_put_pixel(cub->img, x, y++, cub->floor);
}

void	main_loop(void *param)
{
	t_cub	*cub;
	int		x;

	cub = param;
	x = -1;
	while (++x < SCREENWIDTH)
	{
		set_data(cub, x);
		set_side_dist(cub);
		dda(cub);
		set_draw_range(cub);
		draw_floornwalls(cub, x);
		select_texture(cub, x);
		keys_hook(cub);
	}
	usleep(1000);
}
