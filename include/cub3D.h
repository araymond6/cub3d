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
# include <fcntl.h>
# include <ctype.h>
# include <string.h>

#define SCREENWIDTH 640
#define SCREENHEIGHT 480
#define PLAYERBOUND 0.2

// all variables used throughout raycasting, movement and rotation
typedef struct s_var
{
	double		pos[2];
	double		playerdir[2];
	double		camplane[2];
	double		time[2];
	double 		camera;
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

	// used for placing the texture pixels on the appropriate wall
	int				**northarr;
	int				**southarr;
	int				**westarr;
	int				**eastarr;
}	t_texture;

// parsing struct
typedef struct s_map
{
	char **map;
	char	**only_map;
	char	*map_path;
	int		player_pos_x;
	int		player_pos_y;
	int		map_height;
	int		map_width;
	char	playerdir;

	char *NO_path;
	char *SO_path;
	char *WE_path;
	char *EA_path;

	char *f_rgb;
	char *c_rgb;

	int f_red;
	int f_green;
	int f_blue;

	int c_red;
	int c_green;
	int c_blue;

	int start_map_index;
	
} t_map;

typedef struct s_cub
{
	mlx_t				*mlx;
	mlx_image_t			*img;
	uint32_t			ceiling; //ceiling color
	uint32_t			floor; // floor color
	struct s_var		v;
	struct s_texture	texture;
	struct s_map		map;
}	t_cub;


// raycast and mlx functions
void	keys_hook(t_cub *cub);
void	close_hook(void *param);
void	set_data(t_cub *cub, int x);
void	set_side_dist(t_cub *cub);
void	dda(t_cub *cub);
void	set_draw_range(t_cub *cub);
void	main_loop(void *param);
void	init_texture(t_cub *cub);

void	fill_map(t_cub *cub); // TODO: REMOVE WHEN PARSING DONE

//parsing functions
void	check_map_args(t_map *map);
void	get_texture_path(t_map *s_map);
char	*trim_texture_path(char *texture_path);
int		parse_rgb_values(const char *rgbString, t_map *map, int isFloor);
void	read_map(t_map *map);
void findMapDimensions(t_map *map);
void findPlayerPosition(t_map *map);

// all utils
void	init_cub(t_cub *cub);
void	free_int_array(int **arr, int x, int y);
void	free_char_array(char **arr);
void	exit_program(t_cub *cub);
int		get_color(int r, int g, int b, int a);
int		ft_strcmp(const char *str1, const char *str2);
char	*ft_strtok(char *str, const char *delimiters);
void add_zero_map(t_map *map);
void flood_fill(t_map *map, int x, int y);
void print_map(char **map);

#endif