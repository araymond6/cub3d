#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <stdlib.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/src/libft.h"
# include <math.h>
# include <unistd.h>
# include <string.h>
#include <ctype.h>
#include <fcntl.h>

typedef struct s_texture
{
	mlx_texture_t N;
	mlx_texture_t W;
	mlx_texture_t E;
	mlx_texture_t S;
}	t_texture;

typedef struct s_map
{
	char **map;
	char *map_path;

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
	mlx_t	mlx;
}	t_cub;

//functions
int	get_rgba(int r, int g, int b, int a);


void check_map_args(t_map *map);
void get_texture_path(t_map *s_map);
char *trim_texture_path(char *texture_path);
char *ft_strtok(char *str, const char *delimiters);
int ft_strcmp(const char *str1, const char *str2);
int parse_rgb_values(const char *rgbString, t_map *map, int isFloor);
void read_map(t_map *map);

#endif