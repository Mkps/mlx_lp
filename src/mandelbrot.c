#include "../includes/mlx_lp.h"
#include <math.h>
#include <complex.h>

int is_in_set(double x, double y, t_vars *vars)
{
	t_complex	z;
	t_complex	c;
	int			i;

	c.real = x;
	c.imaginary = y;
	z.real = 0;
	z.imaginary = 0;
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

double	ft_lerp(double a, double b, double t)
{
	return (a + t * (b - a));
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
	screen_ratio = (float)vars->window_data.width / vars->window_data.height;
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
int is_in_set_j(double x, double y, t_vars *vars)
{
	t_complex	z;
	int			i;
	double		t;
	z.real = x;
	z.imaginary = y;
	t = 0;
	i = 1;
	while (i < vars->iteration)
	{
		t = z.real;
		z.real = t * t - z.imaginary * z.imaginary + vars->c.real;
		z.imaginary = 2 * z.imaginary * t + vars->c.imaginary;
		if (ft_complex_sqrnorm(z) > 4 * vars->smooth)
			return (i);
		i++;
	}
	return (0);		
}

void ft_julia(t_vars *vars)
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
			iter = is_in_set_j(point_x, point_y, vars);
			ft_color(iter, x, y, vars);
			y+= 0.001 * vars->resolution;
		}
		x += 0.001 * vars->resolution;
	}
}
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
		if ((fabs(z.real - o.real) < 0.0001 && fabs(z.imaginary - o.imaginary) < 0.0001)
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

/** NB: mandel at powers have n - 1 lobes */ 
int is_in_set_flower_6(double x, double y, t_vars *vars)
{
	double	n;
	double	t;
	int	i;
	t_complex z;
	t_complex c;

	i = 1;
	c.real = x;
	c. imaginary = y;
	z.real = 0.0;
	z. imaginary = 0.0;
	n = pow(z.real, 6) + pow(z.imaginary, 6);
	t = 0;
	while (i <= vars->iteration && n < 4)
	{
		t = z.real;
		z.real = pow(z.real, 6) - (15 * pow(z.real, 4) * pow(z.imaginary, 2))
		+ (15 * pow(z.real, 2) * pow(z.imaginary, 4)) - pow(z.imaginary, 6) + c.imaginary;
		z.imaginary = (6 * pow(t, 5) * z.imaginary - 20 * pow(t, 3) * pow(z.imaginary, 3)
		+ 6 * t * pow(z.imaginary, 5)) + c.real;
		n = pow(z.real, 6) + pow(z.imaginary, 6);
		i++;
	}
	if (i >= vars->iteration)
		return (0);
	return (i);		
}

/** NB: mandel at powers have n - 1 lobes */ 
int is_in_set_flower(double x, double y, t_vars *vars)
{
	int	i;
	t_complex z;
	t_complex c;

	i = 1;
	c.real = x;
	c. imaginary = y;
	z.real = 0.0;
	z. imaginary = 0.0;
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

void ft_flower(t_vars *vars)
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
			iter = is_in_set_flower(point_x, point_y, vars);
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
int is_in_set_newton(double x, double y, t_vars *vars)
{
	int			i;
	t_complex	z;
	t_complex	c;
	t_complex	z_num;
	t_complex	z_den;
	t_complex	o;
	t_complex	z2;
	t_complex	z3;
	t_complex	inv;

	z.real = 1;
	z.imaginary = 0;
	c.real = x;
	c.imaginary = y;
	i = 1;
	while (i < vars->iteration)
	{
		o = z;
		z2 = ft_complex_mult(z, z);
		z3 = ft_complex_mult(z2, z);
		z_num.real = ft_complex_pow(z, 4).real; 
		z_num.imaginary = ft_complex_pow(z,4).imaginary; 
		z_den.real = 4 * z3.real;
		z_den.imaginary = 4 * z3.imaginary;
		inv.real = z_den.real;
		inv.imaginary = z_den.imaginary * -1;
		z_num = ft_complex_mult(z_num, inv);
		z_den = ft_complex_mult(z_den, inv);
		if (z_den.real != 0)
		{
			z.real = z_num.real / z_den.real;
			z.imaginary = z_num.imaginary / z_den.real;
		}
		z.real = z.real + c.real;
		z.imaginary = z.imaginary + c.imaginary;
		if (fabs(z.real - o.real) < 0.0000000001 && fabs(z.imaginary - o.imaginary) < 0.0000000001)
		{
			printf("orbit traped at %f + %fi\n", z.real, z.imaginary);
			return (i * ft_complex_sqrnorm(z));
		}
		if (ft_complex_sqrnorm(z) > 4.0)
			return (i * ft_complex_sqrnorm(z));
		i++;
	}
	if (i >= vars->iteration)
		return (0);
	return (i * ft_complex_sqrnorm(z));		
}

void ft_newton(t_vars *vars)
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
			iter = is_in_set_newton(point_x, point_y, vars);
			ft_color(iter, x, y, vars);
			y+= 0.001 * vars->resolution;
		}
		x += 0.001 * vars->resolution;
	}
}
