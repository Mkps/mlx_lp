#include "../includes/mlx_lp.h"

void	init_img(t_vars *vars) {
	int		bpp;
	int		line_length;
	int		endian;
	vars->img.img = mlx_new_image(vars->mlx, vars->window_data.width, vars->window_data.height);
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
	float	offset;

	offset = 0.1 * vars->zoom;	
	if (offset < 0.0000001)
		offset = 0.0000001;
	ft_printf("keycode is %i\n", keycode);
	if (keycode == 65307 || keycode == 27)		
	{
		ft_mlx_exit(vars);
	}
	mlx_destroy_image(vars->mlx, vars->img.img);
	init_img(vars);
	if (keycode == '1')
	{
		vars->c.real = -0.506667;
		vars->c.imaginary = 0.520000;
		vars->fractal = ft_julia;
	}
	if (keycode == '2')
	{
		vars->c.real = 0.18;
		vars->c.imaginary = -0.566667;
		vars->fractal = ft_julia;
	}
	if (keycode == '3')
	{
		vars->c.real = -0.75;
		vars->c.imaginary = 0.0;
		vars->fractal = ft_julia;
	}
	if (keycode == '4')
	{
		vars->c.real = -0.12;
		vars->c.imaginary = 0.75;
		vars->fractal = ft_julia;
	}
	if (keycode == '5')
	{
		vars->c.real = 0.1;
		vars->c.imaginary = 0.65;
		vars->fractal = ft_julia;
	}
	if (keycode == '6')
	{
		vars->c.real = 0.0;
		vars->c.imaginary = -1.0;
		vars->fractal = ft_julia;
	}
	if (keycode == '7')
	{
		vars->c.real = -0.77146;
		vars->c.imaginary = -0.10119;
		vars->fractal = ft_julia;
	}
	if (keycode == 't')
	{
		vars->fractal = ft_mandelbrot;
	}
	if (keycode == 'd')
	{
		vars->offset_x += offset;
	}

	if (keycode == 'a')
		vars->offset_x -= offset;
	if (keycode == 'w')
		vars->offset_y -= offset;
	if (keycode == 's')
		vars->offset_y += offset;
	if (keycode == 'x')
	{
		vars->zoom *= 0.5;
		if (vars->zoom < 0.000000001)
			vars->zoom = 0.000000001;
	}
	if (keycode == 'z')
	{
		vars->zoom *= 1.5;
		if (vars->zoom > 5)
			vars->zoom = 5;
	}
	if (keycode == 'u')
	{
		vars->iteration *= 2;
	}
	if (keycode == 'j')
	{
		vars->iteration *= 0.5;
	}
	if (keycode == 'o')
	{
		vars->resolution *= 0.5;
	}
	if (keycode == 'l')
	{
		vars->resolution *= 1.5;
	}
	if (keycode == 'h')
	{
		if (vars->is_menu_on == 1)
			vars->is_menu_on = 0;
		else
			vars->is_menu_on = 1;
	}
	ft_fractal(vars->fractal, vars);
	mlx_put_image_to_window(vars->mlx, vars->window_data.window_ptr, vars->img.img, 0, 0);
	ft_menu(vars);
	printf("zoom %f offset_x %f\n", vars->zoom, vars->offset_x);	
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

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
