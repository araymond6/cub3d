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

# define SCREENWIDTH 1024
# define SCREENHEIGHT 768
# define PLAYERBOUNDARY 0.2

// for defining what to free in case of error
typedef enum e_error
{
	MAP_ERROR,
	MLX_ERROR
}	t_error;

// all variables used throughout raycasting, movement, rotation and direction
typedef struct s_var
{
	double		pos[2];
	double		playerdir[2];
	double		camplane[2];
	double		time[2];
	double		camera;
	double		raydir[2];
	double		map[2];
	double		sidedist[2];
	double		deltadist[2];
	double		perpwalldist;
	double		step[2];
	double		hit;
	int			side;
	int			lineheight;
	int			drawpoints[2];
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

// parsing struct
typedef struct s_map
{
	char	**map;
	char	**only_map;
	int		player_pos_x;
	int		player_pos_y;
	int		map_height;
	int		map_width;
	char	playerdir;

	char	*map_path;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;

	char	*f_rgb;
	char	*c_rgb;

	int		f_red;
	int		f_green;
	int		f_blue;
	int		c_red;
	int		c_green;
	int		c_blue;

	int		start_map_index;
}	t_map;

typedef struct s_cub
{
	mlx_t				*mlx;
	mlx_image_t			*img;
	uint32_t			ceiling;
	uint32_t			floor;
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
void	set_direction(t_cub *cub);

//parsing functions
void	check_map_args(t_map *map);
void	get_texture_path(t_map *s_map);
char	*trim_texture_path(t_map *s_map, char *texture_path);
int		parse_rgb_values(const char *rgbString, t_map *map, int isFloor);
void	check_rgb_values(t_map *map);
void	read_map(t_map *map);
void	findPlayerPosition(t_map *map);
void	findMapDimensions(t_map *map);
void	set_texture_path(char **dest, char *token, t_map *s_map);
void	wrong_character_in_map(t_map *map);
void	add_zero_map(t_map *map);
int		check_path(char *path);
int		check_extension(char *path, char *extension);
void	check_params(t_map *map);
void	add_zero_map(t_map *map);
void	flood_fill(t_map *map, int x, int y);

// all utils
void	init_cub(t_cub *cub);
void	free_int_array(int **arr, int x, int y);
void	free_char_array(char **arr);
void	free_all(t_cub *cub);
void	free_map(t_map *map);
void	free_texture(t_cub *cub);
void	exit_program(t_cub *cub);
int		get_color(int r, int g, int b, int a);
int		ft_strcmp(const char *str1, const char *str2);
char	*ft_strtok(char *str, const char *delimiters);
void	set_error(void *param, char *error_message, t_error error_type);
int		count_file_size(int fd);
int		count_map_size(t_map *map, int fd);

void	print_map(char **map);

#endif