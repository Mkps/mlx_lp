#include "../includes/mlx_lp.h"

int is_in_set_n(double x, double y, t_vars *vars)
{
	t_complex	z;
	t_complex	z_num;
	t_complex	z_den;
	t_complex	o;
	t_complex	c;
	t_complex	inv;
	int			i;

	z.real = 1;
	z.imaginary = 0;
	c.real = x;
	c.imaginary = y;
	i = 1;
	while (i < vars->iteration)
	{
		o = z;
		z_num.real = ft_complex_pow(z, 3).real - 1; 
		z_num.imaginary = ft_complex_pow(z, 3).imaginary; 
		z_den.real = 3 * ft_complex_pow(z, 2).real;
		z_den.imaginary = 3 * ft_complex_pow(z, 2).imaginary;
		inv.real = z_den.real;
		inv.imaginary = z_den.imaginary * -1;
		z_num = ft_complex_mult(z_num, inv);
		z_den = ft_complex_mult(z_den, inv);
		if (z_den.real != 0)
		{
			z.real = z_num.real / z_den.real;
			z.imaginary = z_num.imaginary / z_den.real;
		}
		z.real = o.real - z.real + c.real;
		z.imaginary = o.imaginary - z.imaginary + c.imaginary;
		if ((fabs(z.real - o.real) < 0.0000000001 && fabs(z.imaginary - o.imaginary) < 0.0000000001)
			|| ft_complex_sqrnorm(z) > 4.0)
			return (i * ft_complex_sqrnorm(z));
		i++;
	}
	return (i * ft_complex_sqrnorm(z));		
}

void ft_nova(t_vars *vars)
{
	double x;
	double y;
	double	point_x;
	double	point_y;
	double	screen_ratio;
	int 	iter;
	double	k;

	screen_ratio = (float)vars->window_data.width / vars->window_data.height;
	k = 2.0 * vars->zoom;
	x = 0.0;
	while (x < 1.0)
	{
		y = 0.0;
		while (y < 1.0) 
		{
			point_x = ft_lerp(-k * screen_ratio + vars->offset_x, k * screen_ratio + vars->offset_x, x);
			point_y = ft_lerp(-k + vars->offset_y, k + vars->offset_y, y);
			iter = is_in_set_n(point_x, point_y, vars);
			ft_color(iter, x, y, vars);
			y+= 0.001 * vars->resolution;
		}
		x += 0.001 * vars->resolution;
	}
}

int is_in_set_ship(double x, double y, t_vars *vars)
{
	int			i;
	t_complex	z;
	t_complex	c;
	t_complex	tmp;

	i = 1;
	c.real = x;
	c. imaginary = y;
	z.real = 0.0;
	z. imaginary = 0.0;
	while (i <= vars->iteration)
	{
		tmp.real = fabs(z.real);
		tmp.imaginary = fabs(z.imaginary);
		z = ft_complex_pow(tmp, vars->power);
		z = ft_complex_add(z, c);
		if (ft_complex_sqrnorm(z)>4)
			return (i);
		i++;
	}
	if (i >= vars->iteration)
		return (0);
	return (i);		
}

void ft_burning_ship(t_vars *vars)
{
	double x;
	double y;
	double	point_x;
	double	point_y;
	double	screen_ratio;
	int 	iter;
	double	k;

	screen_ratio = (float)vars->window_data.width / vars->window_data.height;
	k = 2.0 * vars->zoom;
	x = 0.0;
	while (x < 1.0)
	{
		y = 0.0;
		while (y < 1.0) 
		{
			point_x = ft_lerp(-k * screen_ratio + vars->offset_x, k * screen_ratio + vars->offset_x, x);
			point_y = ft_lerp(-k + vars->offset_y, k + vars->offset_y, y);
			iter = is_in_set_ship(point_x, point_y, vars);
			ft_color(iter, x, y, vars);
			y+= 0.001 * vars->resolution;
		}
		x += 0.001 * vars->resolution;
	}
}

