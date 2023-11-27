#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <stdlib.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/src/libft.h"
# include <math.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>

#define screenWidth 640
#define screenHeight 480
#define mapWidth 6
#define mapHeight 6

typedef struct s_var
{
	double		playerPos[2];
	double		playerDir[2];
	double		camPlane[2];
	double		time[2];
	double 		camera[2];
	double		rayDir[2];
	double		map[2];
	double		sideDist[2];
	double		deltaDist[2];
	double		perpWallDist;
	int			step[2];
	int			hit;
	int			side;
	int			lineHeight;
	int 		drawPoints[2];
	int			color;
	double		frameTime;
	double		moveSpeed;
	double		rotSpeed;
	double		oldDir[2];
	double		oldPlane[2];
}	t_var;

typedef struct s_math
{
	uint32_t	a;
	uint32_t	b;
}	t_math;

typedef struct s_cub
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*textures[4];
	struct s_var	v;
}	t_cub;

//functions
int		get_rgba(int r, int g, int b, int a);
void	keys_hook(mlx_key_data_t keydata, void *param);
void	drawFloor(t_cub *cub);

#endif