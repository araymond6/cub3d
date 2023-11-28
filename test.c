#include "MLX42/include/MLX42/MLX42.h"
#include "include/cub3D.h"

void	closeHook(void *param);
void	keyHook(void *param);

char worldMap[mapWidth][mapHeight] = {
	{1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0 ,1},
	{1, 3, 0, 2, 0 ,1},
	{1, 0, 0, 0, 0 ,1},
	{1, 4, 0, 0, 0 ,1},
	{1, 1, 1, 1, 1, 1}
};

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	verLine(t_cub *cub, int x)
{
	int	i;

	i = cub->v.drawPoints[0];
	while (i < cub->v.drawPoints[1])
	{
		mlx_put_pixel(cub->img, x, i++, cub->v.color);
	}
}

void	keyHook(void *param)
{
	t_cub	*cub;
	if (param)
		cub = param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		closeHook(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
	{
		//both camera direction and camera plane must be rotated
		cub->v.oldDir[0] = cub->v.playerDir[0];
		cub->v.playerDir[0] = cub->v.playerDir[0] * cos(cub->v.rotSpeed) - cub->v.playerDir[1] * sin(cub->v.rotSpeed);
		cub->v.playerDir[1] = cub->v.oldDir[0] * sin(cub->v.rotSpeed) + cub->v.playerDir[1] * cos(cub->v.rotSpeed);
		cub->v.oldPlane[0] = cub->v.camPlane[0];
		cub->v.camPlane[0] = cub->v.camPlane[0] * cos(cub->v.rotSpeed) - cub->v.camPlane[1] * sin(cub->v.rotSpeed);
		cub->v.camPlane[1] = cub->v.oldPlane[0] * sin(cub->v.rotSpeed) + cub->v.camPlane[1] * cos(cub->v.rotSpeed);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
	{
		//both camera direction and camera plane must be rotated
		cub->v.oldDir[0] = cub->v.playerDir[0];
		cub->v.playerDir[0] = cub->v.playerDir[0] * cos(-cub->v.rotSpeed) - cub->v.playerDir[1] * sin(-cub->v.rotSpeed);
		cub->v.playerDir[1] = cub->v.oldDir[0] * sin(-cub->v.rotSpeed) + cub->v.playerDir[1] * cos(-cub->v.rotSpeed);
		cub->v.oldPlane[0] = cub->v.camPlane[0];
		cub->v.camPlane[0] = cub->v.camPlane[0] * cos(-cub->v.rotSpeed) - cub->v.camPlane[1] * sin(-cub->v.rotSpeed);
		cub->v.camPlane[1] = cub->v.oldPlane[0] * sin(-cub->v.rotSpeed) + cub->v.camPlane[1] * cos(-cub->v.rotSpeed);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
	{
		if (worldMap[(int)(cub->v.playerPos[0] + cub->v.playerDir[0] * cub->v.moveSpeed)][(int)cub->v.playerPos[1]] == false)
			cub->v.playerPos[0] += cub->v.playerDir[0] * cub->v.moveSpeed;
		if (worldMap[(int)cub->v.playerPos[0]][(int)(cub->v.playerPos[1] + cub->v.playerDir[1] * cub->v.moveSpeed)] == false)
			cub->v.playerPos[1] += cub->v.playerDir[1] * cub->v.moveSpeed;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
	{
		printf("a\n");
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
	{
		if (worldMap[(int)(cub->v.playerPos[0] - cub->v.playerDir[0] * cub->v.moveSpeed)][(int)cub->v.playerPos[1]] == false)
			cub->v.playerPos[0] -= cub->v.playerDir[0] * cub->v.moveSpeed;
		if (worldMap[(int)cub->v.playerPos[0]][(int)(cub->v.playerPos[1] - cub->v.playerDir[1] * cub->v.moveSpeed)] == false)
			cub->v.playerPos[1] -= cub->v.playerDir[1] * cub->v.moveSpeed;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
	{
		printf("d\n");
	}
}

void castRays(void *param)
{
	t_cub	*cub;
	if (param)
		cub = param;
	for (int x = 0; x < screenWidth; x++)
	{
		cub->v.camera[0] = 2 * x / (double)screenWidth - 1; // x-coordinate in camera space
		cub->v.rayDir[0] = cub->v.playerDir[0] + cub->v.camPlane[0] * cub->v.camera[0];
		cub->v.rayDir[1] = cub->v.playerDir[1] + cub->v.camPlane[1] * cub->v.camera[0];
		//which box of the map we're in
		cub->v.map[0] = (int)cub->v.playerPos[0];
		cub->v.map[1] = (int)cub->v.playerPos[1];
		//length of ray from current position to next x or y-side
		cub->v.deltaDist[0] = (cub->v.rayDir[0] == 0) ? 1e30 : fabs(1 / cub->v.rayDir[0]);
		cub->v.deltaDist[1] = (cub->v.rayDir[1] == 0) ? 1e30 : fabs(1 / cub->v.rayDir[1]);
		//calculate step and initial sideDist
		if (cub->v.rayDir[0] < 0)
		{
			cub->v.step[0] = -1;
			cub->v.sideDist[0] = (cub->v.playerPos[0] - cub->v.map[0]) * cub->v.deltaDist[0];
		}
		else
		{
			cub->v.step[0] = 1;
			cub->v.sideDist[0] = (cub->v.map[0] + 1.0 - cub->v.playerPos[0]) * cub->v.deltaDist[0];
		}
		if (cub->v.rayDir[1] < 0)
		{
			cub->v.step[1] = -1;
			cub->v.sideDist[1] = (cub->v.playerPos[1] - cub->v.map[1]) * cub->v.deltaDist[1];
		}
		else
		{
			cub->v.step[1] = 1;
			cub->v.sideDist[1] = (cub->v.map[1] + 1.0 - cub->v.playerPos[1]) * cub->v.deltaDist[1];
		}
		//perform DDA
		while (cub->v.hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (cub->v.sideDist[0] < cub->v.sideDist[1])
			{
				cub->v.sideDist[0] += cub->v.deltaDist[0];
				cub->v.map[0] += cub->v.step[0];
				cub->v.side = 0;
			}
			else
			{
				cub->v.sideDist[1] += cub->v.deltaDist[1];
				cub->v.map[1] += cub->v.step[1];
				cub->v.side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[(int)cub->v.map[0]][(int)cub->v.map[1]] > 0)
				cub->v.hit = 1;
		}
		//Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
		if (cub->v.side == 0)
			cub->v.perpWallDist = (cub->v.sideDist[0] - cub->v.deltaDist[0]);
		else
			cub->v.perpWallDist = (cub->v.sideDist[1] - cub->v.deltaDist[1]);
		//Calcyulate height of line to draw on screen
		cub->v.lineHeight = (int)(screenHeight / cub->v.perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		cub->v.drawPoints[0] = -cub->v.lineHeight / 2 + screenHeight / 2;
		if (cub->v.drawPoints[0] < 0)
			cub->v.drawPoints[0] = 0;
		cub->v.drawPoints[1] = cub->v.lineHeight / 2 + screenHeight / 2;
		if (cub->v.drawPoints[1] >= screenHeight)
			cub->v.drawPoints[1] = screenHeight - 1;
		//choose wall color
		switch (worldMap[(int)cub->v.map[0]][(int)cub->v.map[1]])
		{
			case 1:  cub->v.color = get_rgba(255, 0, 0, 255);  break; //red
			case 2:  cub->v.color = get_rgba(0, 255, 0, 255);  break; //green
			case 3:  cub->v.color = get_rgba(0, 0, 255, 255);  break; //blue
			case 4:  cub->v.color = get_rgba(255, 255, 255, 255);  break; //white
			default: cub->v.color = get_rgba(255, 255, 0, 255); break; //yellow
		}
		//give x and y sides different brightness
		if (cub->v.side == 1)
			cub->v.color = cub->v.color / 2;
		//draw the pixels of the stripe as a vertical line
		verLine(cub, x);
	}
	//timing for input and FPS counter
	cub->v.time[1] = cub->v.time[0];
	cub->v.time[0] = mlx_get_time();
	//frameTime is the time this frame has taken, in seconds
	cub->v.frameTime = (cub->v.time[0] - cub->v.time[1]) / 1000.0;
	printf("%d\n", (int)(1.0 / cub->v.frameTime)); //FPS counter
	mlx_image_to_window(cub->mlx, cub->img, 0, 0);
	mlx_new_image(cub->mlx, screenWidth, screenHeight);

	//speed modifiers
	cub->v.moveSpeed = cub->v.frameTime * 5.0; //the constant value is in squares/second
	cub->v.rotSpeed = cub->v.frameTime * 3.0; //the constant value is in radians/second
	mlx_loop_hook(cub->mlx, &keyHook, cub);
}

void	init_cub(t_cub *cub)
{
	ft_bzero(cub, sizeof(t_cub));
}


void	closeHook(void *param)
{
	t_cub	*cub;
	if (param)
		cub = param;
	mlx_close_window(cub->mlx);
	mlx_terminate(cub->mlx);
	exit(0);
}

int main()
{
	t_cub	cub;
	
	ft_bzero(&cub, sizeof(t_cub));
	cub.mlx = mlx_init(screenWidth, screenHeight, "Raycaster", 1);
	cub.img = mlx_new_image(cub.mlx, screenWidth, screenHeight);
	cub.v.playerPos[0] = 4;
	cub.v.playerPos[1] = 4;
	cub.v.playerDir[0] = -1;
	cub.v.playerDir[1] = 0;
	cub.v.camPlane[0] = 0;
	cub.v.camPlane[1] = 0.66;
	mlx_loop_hook(cub.mlx, &castRays, &cub);
	mlx_close_hook(cub.mlx, closeHook, &cub);
	mlx_loop(cub.mlx);

	return 0;
}
