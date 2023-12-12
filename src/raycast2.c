#include "../include/cub3D.h"

/*
	sets and normalises ray directon, floored map position and the distance 
	needed by the ray for each step it takes (deltadist)
*/ 
void	set_data(t_cub *cub, int x)
{
	cub->v.camera = 2 * x / (double)SCREENWIDTH - 1;
	cub->v.raydir[0] = cub->v.playerdir[0]
		+ cub->v.camplane[0] * cub->v.camera;
	cub->v.raydir[1] = cub->v.playerdir[1]
		+ cub->v.camplane[1] * cub->v.camera;
	cub->v.map[0] = (int)cub->v.pos[0];
	cub->v.map[1] = (int)cub->v.pos[1];
	cub->v.deltadist[0] = fabs(1 / cub->v.raydir[0]);
	cub->v.deltadist[1] = fabs(1 / cub->v.raydir[1]);
}

void	set_side_dist(t_cub *cub)
{
	if (cub->v.raydir[0] < 0)
	{
		cub->v.step[0] = -1;
		cub->v.sidedist[0] = (cub->v.pos[0] - cub->v.map[0])
			* cub->v.deltadist[0];
	}
	else
	{
		cub->v.step[0] = 1;
		cub->v.sidedist[0] = (cub->v.map[0] + 1.0 - cub->v.pos[0])
			* cub->v.deltadist[0];
	}
	if (cub->v.raydir[1] < 0)
	{
		cub->v.step[1] = -1;
		cub->v.sidedist[1] = (cub->v.pos[1] - cub->v.map[1])
			* cub->v.deltadist[1];
	}
	else
	{
		cub->v.step[1] = 1;
		cub->v.sidedist[1] = (cub->v.map[1] + 1.0 - cub->v.pos[1])
			* cub->v.deltadist[1];
	}
}

void	dda_calc(t_cub *cub)
{
	if (cub->v.sidedist[0] < cub->v.sidedist[1])
	{
		cub->v.sidedist[0] += cub->v.deltadist[0];
		cub->v.map[0] += cub->v.step[0];
		if (cub->v.raydir[0] > 0)
			cub->v.side = 0;
		else
			cub->v.side = 1;
	}
	else
	{
		cub->v.sidedist[1] += cub->v.deltadist[1];
		cub->v.map[1] += cub->v.step[1];
		if (cub->v.raydir[1] > 0)
			cub->v.side = 2;
		else
			cub->v.side = 3;
	}
}

// DDA stands for Digital Differential Analyzer
// algorithm for looking at grid cells. calculates the intersections
// incrementally along the ray path
void	dda(t_cub *cub)
{
	while (1)
	{
		if (cub->map.map[(int)cub->v.map[0]][(int)cub->v.map[1]] == '1')
			break ;
		else
			dda_calc(cub);
	}
	if (cub->v.side < 2)
		cub->v.perpwalldist = (cub->v.sidedist[0] - cub->v.deltadist[0]);
	else
		cub->v.perpwalldist = (cub->v.sidedist[1] - cub->v.deltadist[1]);
}

// sets the draw range to draw the wall at the appropriate height
void	set_draw_range(t_cub *cub)
{
	cub->v.lineheight = (int)SCREENHEIGHT / cub->v.perpwalldist;
	cub->v.drawpoints[0] = -cub->v.lineheight * 0.5 + SCREENHEIGHT
		* cub->v.camangle;
	if (cub->v.drawpoints[0] < 0)
		cub->v.drawpoints[0] = 0;
	cub->v.drawpoints[1] = cub->v.lineheight * 0.5 + SCREENHEIGHT
		* cub->v.camangle;
	if (cub->v.drawpoints[1] >= SCREENHEIGHT)
		cub->v.drawpoints[1] = SCREENHEIGHT;
}
