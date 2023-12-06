#include "../include/cub3D.h"

void	rotate_player(double *vec_x, double *vec_y, double dir);
void	strafe_player(t_cub *cub, double movespeed);
void	move_player(t_cub *cub, double movespeed);

void	keys_hook(t_cub *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		close_hook(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W) || 
		mlx_is_key_down(cub->mlx, MLX_KEY_UP))
		move_player(cub, cub->v.movespeed);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S) || 
		mlx_is_key_down(cub->mlx, MLX_KEY_DOWN))
		move_player(cub, -cub->v.movespeed);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		strafe_player(cub, -cub->v.movespeed);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		strafe_player(cub, cub->v.movespeed);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
	{
		rotate_player(&cub->v.playerdir[0], &cub->v.playerdir[1], cub->v.rotspeed);
		rotate_player(&cub->v.camplane[0], &cub->v.camplane[1], cub->v.rotspeed);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
	{
		rotate_player(&cub->v.playerdir[0], &cub->v.playerdir[1], -cub->v.rotspeed);
		rotate_player(&cub->v.camplane[0], &cub->v.camplane[1], -cub->v.rotspeed);
	}
}

void	rotate_player(double *vec_x, double *vec_y, double dir)
{
	double	x;

	x = *vec_x;
	*vec_x = x * cos(dir) - *vec_y * sin(dir);
	*vec_y = x * sin(dir) + *vec_y * cos(dir);
}

// checks if the new position is inbound or not
static int	is_wall(t_cub *cub, double new_pos[2], double movespeed)
{
	return (cub->map.map[(int)(new_pos[0])][(int)(new_pos[1])] == '1');
}

// updates player movement depending on if new_pos is in a wall or not
void	move_player(t_cub *cub, double movespeed)
{
	double	new_pos[2];

	new_pos[0] = cub->v.pos[0] + cub->v.playerdir[0] * movespeed;
	new_pos[1] = cub->v.pos[1] + cub->v.playerdir[1] * movespeed;
	if (!is_wall(cub, new_pos, movespeed))
	{
		cub->v.pos[0] = new_pos[0];
		cub->v.pos[1] = new_pos[1];
	}
}

// updates player movement depending on if new_pos is in a wall or not
void	strafe_player(t_cub *cub, double movespeed)
{
	double	new_pos[2];

	new_pos[0] = cub->v.pos[0] + cub->v.playerdir[1] * movespeed;
	new_pos[1] = cub->v.pos[1] - cub->v.playerdir[0] * movespeed;
	if (!is_wall(cub, new_pos, movespeed))
	{
		cub->v.pos[0] = new_pos[0];
		cub->v.pos[1] = new_pos[1];
	}
}

// if (cub->map[(int)cub->v.pos[0]][(int)(cub->v.pos[1] + 
// 	cub->v.playerdir[0] * (movespeed + checkradius))] == '0')