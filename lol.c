#include "MLX42/include/MLX42/MLX42.h"

int main()
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int		x;
	int		y;

	mlx = mlx_init(500, 500, "test", 0);
	img = mlx_new_image(mlx, 500, 500);
	x = 0;
	y = 0;
	while (x < 500)
	{
		while (y < 500)
		{
			mlx_put_pixel(img, x, y, 0x00FF00FF);
			y++;
		}
		y = 0;
		x++;
	}
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop(mlx);
	return (0);
}