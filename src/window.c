#include "../includes/mlx_lp.h"

void	init_img(t_vars *vars) {
	int		bpp;
	int		line_length;
	int		endian;
	vars->img.img = mlx_new_image(vars->mlx, 1000, 1000);
	vars->img.addr = mlx_get_data_addr(vars->img.img, &bpp, &line_length, &endian);
	vars->img.line_length = line_length;
	vars->img.bits_per_pixel = bpp;
	vars->img.endian = endian;
}
void	ft_mlx_exit(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img.img);
	mlx_destroy_window(vars->mlx, vars->window_data.window_ptr);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
}
int	ft_mlx_key_hook(int keycode, t_vars *vars)
{
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
		ft_julia(vars);
		mlx_put_image_to_window(vars->mlx, vars->window_data.window_ptr, vars->img.img, 0, 0);
	}
	if (keycode == '2')
	{
		mlx_destroy_image(vars->mlx, vars->img.img);
		vars->c.real = 0.18;
		vars->c.imaginary = -0.566667;
		init_img(vars);
		ft_julia(vars);
		mlx_put_image_to_window(vars->mlx, vars->window_data.window_ptr, vars->img.img, 0, 0);
	}
	if (keycode == 'd')
	{
		mlx_destroy_image(vars->mlx, vars->img.img);
		init_img(vars);
		vars->offset_x += 0.005;
		ft_julia(vars);
		mlx_put_image_to_window(vars->mlx, vars->window_data.window_ptr, vars->img.img, 0, 0);
	}

	if (keycode == 'a')
	{
		mlx_destroy_image(vars->mlx, vars->img.img);
		init_img(vars);
		vars->offset_x -= 0.005;
		ft_julia(vars);
		mlx_put_image_to_window(vars->mlx, vars->window_data.window_ptr, vars->img.img, 0, 0);
	}
	if (keycode == 'w')
	{
		mlx_destroy_image(vars->mlx, vars->img.img);
		init_img(vars);
		vars->offset_y -= 0.005;
		ft_julia(vars);
		mlx_put_image_to_window(vars->mlx, vars->window_data.window_ptr, vars->img.img, 0, 0);
	}

	if (keycode == 's')
	{
		mlx_destroy_image(vars->mlx, vars->img.img);
		init_img(vars);
		vars->offset_y += 0.005;
		ft_julia(vars);
		mlx_put_image_to_window(vars->mlx, vars->window_data.window_ptr, vars->img.img, 0, 0);
	}
	if (keycode == 'x')
	{
		mlx_destroy_image(vars->mlx, vars->img.img);
		init_img(vars);
		vars->zoom *= 0.95;
		ft_julia(vars);
		mlx_put_image_to_window(vars->mlx, vars->window_data.window_ptr, vars->img.img, 0, 0);
	}
	if (keycode == 'z')
	{
		mlx_destroy_image(vars->mlx, vars->img.img);
		init_img(vars);
		vars->zoom *= 1.05;
		ft_julia(vars);
		mlx_put_image_to_window(vars->mlx, vars->window_data.window_ptr, vars->img.img, 0, 0);
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
