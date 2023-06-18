#include "../includes/mlx_lp.h"

void	ft_mlx_exit(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img->img);
	mlx_destroy_window(vars->mlx, vars->window);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
}
int	ft_mlx_close_window(int keycode, t_vars *vars)
{
	ft_printf("keycode is %i\n", keycode);
	if (keycode == 65307 || keycode == 27)
	{
		ft_mlx_exit(vars);
	}
	return (0);
}

int ft_mlx_destroy_hook(t_vars *vars)
{
	ft_mlx_exit(vars);
	return (0);
}
void	ft_mlx_fill(t_data img, int size_x, int size_y, int color)
{
	int x;
  	int y;

	x = 0;
  	y = 0;
  	while (y < size_y)
  	{
    	x = 0;
		while(x < size_x)
		{
			ft_mlx_pixel_put(&img, x, y, color);
   			x++;
   		}
   		y++;
  	}
}

int   create_argb(int a, int r, int g, int b)
{
  	return (a << 24 | r << 16 | g << 8 | b);
}

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
