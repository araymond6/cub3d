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
#define mapWidth 24
#define mapHeight 24

typedef struct s_var
{
	double		pos[2];
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
	double		hit;
	int			side;
	int			lineHeight;
	int 		drawPoints[2];
	int			color;
	double		frameTime;
	double		moveSpeed;
	double		rotSpeed;
	double		oldDir[2];
	double		oldPlane[2];
	double		camAngle;
	int			texture;
}	t_var;

typedef struct s_texture
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	int				**northArr;
	int				**southArr;
	int				**westArr;
	int				**eastArr;
}	t_texture;

typedef struct s_cub
{
	mlx_t				*mlx;
	mlx_image_t			*img;
	char				**map;
	uint32_t			ceiling;
	uint32_t			floor;
	struct s_var		v;
	struct s_texture	texture;
}	t_cub;

//functions
int		getColor(int r, int g, int b, int a);
void	keysHook(t_cub *cub);
void	closeHook(void *param);
void	setData(t_cub *cub, int x);
void	setSideDist(t_cub *cub);
void	dda(t_cub *cub);
void	setDrawRange(t_cub *cub);
void	mainLoop(void *param);

#endif