#include "../include/cub3D.h"

void	rotate_player(double *vec_x, double *vec_y, double dir);
void	strafe_player(t_cub *cub, double movespeed);
void	move_player(t_cub *cub, double movespeed);

static void	rotate_movement(t_cub *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
	{
		rotate_player(&cub->v.playerdir[0], &cub->v.playerdir[1], \
		cub->v.rotspeed);
		rotate_player(&cub->v.camplane[0], &cub->v.camplane[1], \
		cub->v.rotspeed);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
	{
		rotate_player(&cub->v.playerdir[0], &cub->v.playerdir[1], \
		-cub->v.rotspeed);
		rotate_player(&cub->v.camplane[0], &cub->v.camplane[1], \
		-cub->v.rotspeed);
	}
}

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
	rotate_movement(cub);
}

// increments or decrements player's rotation
void	rotate_player(double *vec_x, double *vec_y, double dir)
{
	double	x;

	x = *vec_x;
	*vec_x = x * cos(dir) - *vec_y * sin(dir);
	*vec_y = x * sin(dir) + *vec_y * cos(dir);
}

/*
moves the player forward of backwards if it's inbound, 
while adding a boundary limit to the player's position
*/ 
void	move_player(t_cub *cub, double movespeed)
{
	double	boundary;

	boundary = PLAYERBOUNDARY;
	if (movespeed < 0)
		boundary = -PLAYERBOUNDARY;
	if (cub->map.map[(int)(cub->v.pos[0] + cub->v.playerdir[0] * \
		(movespeed + boundary))][(int)cub->v.pos[1]] == '0')
		cub->v.pos[0] += cub->v.playerdir[0] * movespeed;
	if (cub->map.map[(int)cub->v.pos[0]][(int)(cub->v.pos[1] + \
		cub->v.playerdir[1] * (movespeed + boundary))] == '0')
		cub->v.pos[1] += cub->v.playerdir[1] * movespeed;
}

/*
moves the player sideways if it's inbound, 
while adding a boundary limit to the player's position
*/ 
void	strafe_player(t_cub *cub, double movespeed)
{
	double	boundary;

	boundary = PLAYERBOUNDARY;
	if (movespeed < 0)
		boundary = -PLAYERBOUNDARY;
	if (cub->map.map[(int)(cub->v.pos[0] + cub->v.playerdir[1] * \
		(movespeed + boundary))][(int)cub->v.pos[1]] != '1')
		cub->v.pos[0] += cub->v.playerdir[1] * movespeed;
	if (cub->map.map[(int)cub->v.pos[0]][(int)(cub->v.pos[1] - \
		cub->v.playerdir[0] * (movespeed + boundary))] != '1')
		cub->v.pos[1] -= cub->v.playerdir[0] * movespeed;
}
