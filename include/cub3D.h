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


typedef struct s_var
{
	int	px;
	int	py;
	double	moveSpeed;
	double	rotSpeed;
	double	dirX;
	double	dirY;

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

#endif