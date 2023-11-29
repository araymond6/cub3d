#include "../include/cub3D.h"

void	findHit(t_cub *cub, mlx_texture_t *texture)
{
	cub->v.hit = 0;
	if (cub->v.side == 0 || cub->v.side == 1)
	{
		cub->v.hit = cub->v.playerPos[1] + cub->v.perpWallDist *
		cub->v.rayDir[1];
	}
	else
	{
		cub->v.hit = cub->v.playerPos[0] + cub->v.perpWallDist *
		cub->v.rayDir[0];
	}
	cub->v.hit -= cub->v.hit;
	cub->v.texture = ((int)cub->v.hit * (double)texture->width);
	if ((cub->v.side == 0 || cub->v.side == 1) && cub->v.rayDir[0] > 0)
		cub->v.texture = texture->width - cub->v.texture - 1;
	if ((cub->v.side == 2 || cub->v.side == 3) && cub->v.rayDir[1] < 0)
		cub->v.texture = texture->width - cub->v.texture - 1;
}

void	drawLine(t_cub *cub, mlx_texture_t *texture, uint32_t **ar, int x)
{
	double	dist;
	double	pos;
	int		tex_y;
	int		j;

	dist = 1.0 * texture->height / cub->v.lineHeight;
	pos = ((double) cub->v.drawPoints[0] - (double)screenHeight / 2
			+ (double) cub->v.lineHeight / 2) * dist;
	if (pos < 0)
		pos = 0;
	j = cub->v.drawPoints[0] - 1;
	while (++j < cub->v.drawPoints[1])
	{
		tex_y = (int) pos;
		if (pos > texture->height - 1)
			pos = texture->height - 1;
		pos += dist;
		mlx_put_pixel(cub->img, x, j, ar[tex_y][cub->v.texture]);
	}
}

void	selectTexture(t_cub *cub, int x)
{
	if (cub->v.side == 0)
	{
		findHit(cub, cub->texture.south);
		drawLine(cub, cub->texture.south, cub->texture.southArr, x);
	}
	if (cub->v.side == 1)
	{
		findHit(cub, cub->texture.north);
		drawLine(cub, cub->texture.north, cub->texture.northArr, x);
	}
	if (cub->v.side == 2)
	{
		findHit(cub, cub->texture.east);
		drawLine(cub, cub->texture.east, cub->texture.eastArr, x);
	}
	if (cub->v.side == 3)
	{
		findHit(cub, cub->texture.west);
		drawLine(cub, cub->texture.west, cub->texture.westArr, x);
	}
}

void	vertLine(t_cub *cub, int x)
{
	int	y;

	y = 0;
	while (y < cub->v.drawPoints[0])
		mlx_put_pixel(cub->img, x, y++, cub->ceiling);
	while (y < screenHeight)
		mlx_put_pixel(cub->img, x, y++, cub->floor);
}

void	mainLoop(void *param)
{
	t_cub	*cub;
	int		x;

	cub = param;
	x = -1;
	while (++x < screenHeight)
	{
		setData(cub, x);
		setSideDist(cub);
		dda(cub);
		setDrawRange(cub);
		vertLine(cub, x);
		selectTexture(cub, x);
		key_binding(cub);
	}
	//track_window(cub); //what is this
	usleep(1500);
}