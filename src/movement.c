#include "../include/cub3D.h"

void	rotate_player(int *new_vector, double dir);
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
		rotate_player(cub->v.playerdir, cub->v.rotspeed);
		rotate_player(cub->v.camplane, cub->v.rotspeed);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
	{
		rotate_player(cub->v.playerdir, -cub->v.rotspeed);
		rotate_player(cub->v.camplane, -cub->v.rotspeed);
	}
}

void	rotate_player(int *new_vector, double dir)
{
	double	x;

	x = new_vector[0];
	new_vector[0] = x * cos(dir) - new_vector[1] * sin(dir);
	new_vector[1] = x * sin(dir) + new_vector[1] * cos(dir);
}

void	move_player(t_cub *cub, double movespeed)
{
	double	checkradius;

	checkradius = 0.5; // change this
	if (movespeed < 0)
		checkradius = -checkradius;
	if (cub->map[(int)(cub->v.pos[0] + cub->v.playerdir[0] * \
		(movespeed + checkradius))][(int)cub->v.pos[1]] == '0')
		cub->v.pos[0] += cub->v.playerdir[0] * movespeed;
	if (cub->map[(int)cub->v.pos[0]][(int)(cub->v.pos[1] + \
		cub->v.playerdir[1] * (movespeed + checkradius))])
		cub->v.pos[1] += cub->v.playerdir[1] * movespeed;
}

void	strafe_player(t_cub *cub, double movespeed)
{
	double	checkradius;

	checkradius = 0.5; // change this to define
	if (movespeed < 0)
		checkradius = -checkradius;
	if (cub->map[(int)(cub->v.pos[0] + cub->v.playerdir[1] * \
		(movespeed + checkradius))][(int)cub->v.pos[1]] == '0')
		cub->v.pos[0] += cub->v.playerdir[0] * movespeed;
	if (cub->map[(int)cub->v.pos[0]][(int)(cub->v.pos[1] + \
		cub->v.playerdir[0] * (movespeed + checkradius))])
		cub->v.pos[1] += cub->v.playerdir[1] * movespeed;
}