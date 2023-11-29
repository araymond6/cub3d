#include "../include/cub3D.h"

void	setData(t_cub *cub, int x)
{
	cub->v.camera[0] = 2 * x / (double)screenWidth - 1;
	cub->v.rayDir[0] = cub->v.playerDir[0]
		+ cub->v.camPlane[0] * cub->v.camera[0];
	cub->v.rayDir[1] = cub->v.playerDir[1]
		+ cub->v.camPlane[1] * cub->v.camera[0];
	cub->v.map[0] = (int)cub->v.pos[0];
	cub->v.map[1] = (int)cub->v.pos[1];
	cub->v.deltaDist[0] = fabs(1 / cub->v.rayDir[0]);
	cub->v.deltaDist[1] = fabs(1 / cub->v.rayDir[1]);
}

void	setSideDist(t_cub *cub)
{
	if (cub->v.rayDir[0] < 0)
	{
		cub->v.step[0] = -1;
		cub->v.sideDist[0] = (cub->v.pos[0] - cub->v.map[0])
			* cub->v.deltaDist[0];
	}
	else
	{
		cub->v.step[0] = 1;
		cub->v.sideDist[0] = (cub->v.map[0] + 1.0 - cub->v.pos[0])
			* cub->v.deltaDist[0];
	}
	if (cub->v.rayDir[1] < 0)
	{
		cub->v.step[1] = -1;
		cub->v.sideDist[1] = (cub->v.pos[1] - cub->v.map[1])
			* cub->v.deltaDist[1];
	}
	else
	{
		cub->v.step[1] = 1;
		cub->v.sideDist[1] = (cub->v.map[1] + 1.0 - cub->v.pos[1])
			* cub->v.deltaDist[1];
	}
}

void	dda_calc(t_cub *cub)
{
	if (cub->v.sideDist[0] < cub->v.sideDist[1])
	{
		cub->v.sideDist[0] += cub->v.deltaDist[0];
		cub->v.map[0] += cub->v.step[0];
		if (cub->v.rayDir[0] > 0)
			cub->v.side = 0;
		else
			cub->v.side = 1;
	}
	else
	{
		cub->v.sideDist[1] += cub->v.deltaDist[1];
		cub->v.map[1] += cub->v.step[1];
		if (cub->v.rayDir[1] > 0)
			cub->v.side = 2;
		else
			cub->v.side = 3;
	}
}

void	dda(t_cub *cub)
{
	while (1)
	{
		dda_calc(cub);
		if (cub->map[(int)cub->v.map[0]][(int)cub->v.map[1]] == '1')
			break ;
	}
	if (cub->v.side < 2)
		cub->v.perpWallDist = (cub->v.sideDist[0]
				- cub->v.deltaDist[0]);
	else
		cub->v.perpWallDist = (cub->v.sideDist[1]
				- cub->v.deltaDist[1]);
}

void	setDrawRange(t_cub *cub)
{
	cub->v.lineHeight = (int)screenHeight / cub->v.perpWallDist;
	cub->v.drawPoints[0] = -cub->v.lineHeight * 0.5 + screenHeight
		* cub->v.camAngle;
	if (cub->v.drawPoints[0] < 0)
		cub->v.drawPoints[0] = 0;
	cub->v.drawPoints[1] = cub->v.lineHeight * 0.5 + screenHeight
		* cub->v.camAngle;
	if (cub->v.drawPoints[1] >= screenHeight)
		cub->v.drawPoints[1] = screenHeight;
}