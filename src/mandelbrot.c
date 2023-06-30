#include "../includes/mlx_lp.h"

int is_in_set(double x, double y, t_vars *vars)
{
	t_complex	z;
	t_complex	c;
	int			i;

	c.r = x;
	c.i = y;
	z.r = 0;
	z.i = 0;
	i = 1;
	while (i < vars->iteration)
	{
		z = ft_complex_pow(z, 2);
		z = ft_complex_add(z, c);
		if (ft_complex_sqrnorm(z) > 4.0 * vars->smooth)
			return (i);
		i++;
	}
	return (0);
}


void ft_mandelbrot(t_vars *vars)
{
	double	x;
	double	y;
	double	point_x;
	double	point_y;
	int 	iter;
	double	k;
	double	screen_ratio;

	k = 2.0 * vars->zoom;
	screen_ratio = (float)vars->w_data.width / vars->w_data.height;
	x = 0.0;
	while (x < 1.0)
	{
		y = 0.0;
		while (y < 1.0) 
		{
			point_x = ft_lerp(-k * screen_ratio + vars->offset_x, k * screen_ratio + vars->offset_x, x);
			point_y = ft_lerp(-k + vars->offset_y, k + vars->offset_y, y);
			iter = is_in_set(point_x, point_y, vars);
			ft_color(iter, x, y, vars);
			y+= 0.001 * vars->resolution;
		}
		x += 0.001 * vars->resolution;
	}
}

/** NB: mandel at powers have n - 1 lobes */ 
static int is_in_set_power(double x, double y, t_vars *vars)
{
	int	i;
	t_complex z;
	t_complex c;

	i = 1;
	c.r = x;
	c. i = y;
	z.r = 0.0;
	z. i = 0.0;
	while (i <= vars->iteration)
	{
		z = ft_complex_pow(z, vars->power);
		z = ft_complex_add(z, c);
		if (ft_complex_sqrnorm(z)>4)
			return (i);
		i++;
	}
	if (i >= vars->iteration)
		return (0);
	return (i);		
}

void ft_power(t_vars *vars)
{
	double x;
	double y;
	double	point_x;
	double	point_y;
	double	screen_ratio;
	int 	iter;
	double	k;

	screen_ratio = (float)vars->w_data.width / vars->w_data.height;
	k = 2.0 * vars->zoom;
	x = 0.0;
	while (x < 1.0)
	{
		y = 0.0;
		while (y < 1.0) 
		{
			point_x = ft_lerp(-k * screen_ratio + vars->offset_x, k * screen_ratio + vars->offset_x, x);
			point_y = ft_lerp(-k + vars->offset_y, k + vars->offset_y, y);
			iter = is_in_set_power(point_x, point_y, vars);
			ft_color(iter, x, y, vars);
			y+= 0.001 * vars->resolution;
		}
		x += 0.001 * vars->resolution;
	}
}


