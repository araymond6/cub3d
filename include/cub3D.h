#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/src/libft.h"
//# include "../libft/42_garbage_collector/lib/ft_gc.h"
# include <math.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>

#define SCREENWIDTH 640
#define SCREENHEIGHT 480
#define MAPWIDTH 8
#define MAPHEIGHT 8
#define PLAYERBOUND 0.5

typedef struct s_var
{
	double		pos[2];
	double		playerdir[2];
	double		camplane[2];
	double		time[2];
	double 		camera[2];
	double		raydir[2];
	double		map[2];
	double		sidedist[2];
	double		deltadist[2];
	double		perpwalldist;
	double		step[2];
	double		hit;
	int			side;
	int			lineheight;
	int 		drawpoints[2];
	int			color;
	double		frametime;
	double		movespeed;
	double		rotspeed;
	double		olddir[2];
	double		oldplane[2];
	double		camangle;
	int			texture;
}	t_var;

typedef struct s_texture
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	int				**northarr;
	int				**southarr;
	int				**westarr;
	int				**eastarr;
}	t_texture;

typedef struct s_cub
{
	mlx_t				*mlx;
	mlx_image_t			*img;
	char				**map;
	uint32_t			ceiling;
	uint32_t			floor;
	int					mapheight;
	int					mapwidth;
	struct s_var		v;
	struct s_texture	texture;
}	t_cub;

//functions
int		get_color(int r, int g, int b, int a);
void	keys_hook(t_cub *cub);
void	close_hook(void *param);
void	set_data(t_cub *cub, int x);
void	set_side_dist(t_cub *cub);
void	dda(t_cub *cub);
void	set_draw_range(t_cub *cub);
void	main_loop(void *param);
void	free_array(char **arr);
void	exit_program(t_cub *cub);
void	fill_map(t_cub *cub); // TODO: REMOVE WHEN PARSING DONE
void	init_texture(t_cub *cub);

#endif