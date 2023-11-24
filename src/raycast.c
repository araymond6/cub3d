#include "../include/cub3D.h"


#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

int worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void verLine(t_cub *cub, int x, int drawStart, int drawEnd, int color)
{
	int	i;

	i = drawStart;

	while (i < drawEnd)
	{
		mlx_put_pixel(cub->img, x, i++, color);
	}
}

void	drawFloor(t_cub *cub)
{
	double posX = 22, posY = 12;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame
	cub->mlx = mlx_init(screenWidth, screenHeight, "Minecraft", 0);
	mlx_new_image(cub->mlx, screenWidth, screenHeight);
	// start of calculation loop
	for(int x = 0; x < screenWidth; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		//which box of the map we're in
		int mapX = (int)posX;
		int mapY = (int)posY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirX == 0) ? 1e30 : abs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : abs(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0) hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if(side == 0)	perpWallDist = (sideDistX - deltaDistX);
		else			perpWallDist = (sideDistY - deltaDistY);
		//Calculate height of line to draw on screen
		int lineHeight = (int)(screenHeight / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if(drawEnd >= screenHeight)drawEnd = screenHeight - 1;
		//choose wall color
		int color;
		switch(worldMap[mapX][mapY])
		{
			case 1:  color = get_rgba(255, 0, 0, 255);  break; //red
			case 2:  color = get_rgba(0, 255, 0, 255);  break; //green
			case 3:  color = get_rgba(0, 0, 255, 255);   break; //blue
			case 4:  color = get_rgba(0, 0, 0, 255);  break; //white
			default: color = get_rgba(0, 255, 255, 255); break; //yellow
		}
		// //give x and y sides different brightness
		// if (side == 1) {color = color / 2;}

		//draw the pixels of the stripe as a vertical line
		verLine(cub, x, drawStart, drawEnd, color);
	}
	//timing for input and FPS counter
	oldTime = time;
	time = getTicks();
	double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
	printf("%d", 1.0 / frameTime); //FPS counter
	redraw();
	cls();

	//speed modifiers
	double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
	double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
	mlx_key_hook(cub->mlx, keys_hook, cub);
	mlx_loop(cub->mlx);
}
