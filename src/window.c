#include "../includes/mlx_lp.h"

void	init_img(t_vars *vars)
{
	int		bpp;
	int		line_length;
	int		endian;
	vars->img.img = mlx_new_image(vars->mlx, 1000, 1000);
	vars->img.addr = mlx_get_data_addr(vars->img.img, &bpp, &line_length, &endian);
	vars->img.line_length = line_length;
	vars->img.bits_per_pixel = bpp;
	vars->img.endian = endian;
	vars->img.zoom = 1.0;
	vars->img.offset = 0.0;
}
void	ft_mlx_exit(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img.img);
	mlx_destroy_window(vars->mlx, vars->window);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
}
int	ft_mlx_key_hook(int keycode, t_vars *vars)
{
	t_complex c;

	c.real = 0;
	c.imaginary = 0;
	ft_printf("keycode is %i\n", keycode);
	if (keycode == 65307 || keycode == 27)		
	{
		ft_mlx_exit(vars);
	}
	if (keycode == '1')
	{
		mlx_destroy_image(vars->mlx, vars->img.img);
		vars->c.real = -0.506667;
		vars->c.imaginary = 0.520000;
		init_img(vars);
		ft_julia(vars->img, 1000, 1000, vars->c);
		mlx_put_image_to_window(vars->mlx, vars->window, vars->img.img, 0, 0);
	}
	if (keycode == '2')
	{
		mlx_destroy_image(vars->mlx, vars->img.img);
		c.real = 0.18;
		c.imaginary = -0.566667;
		init_img(vars);
		ft_julia(vars->img, 1000, 1000, c);
		mlx_put_image_to_window(vars->mlx, vars->window, vars->img.img, 0, 0);
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
