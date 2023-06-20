#include "../includes/mlx_lp.h"
#include <math.h>
t_complex ft_complex_add(t_complex c1, t_complex c2)
{
	t_complex tmp;

	tmp.real = c1.real + c2.real;
	tmp.imaginary = c1.imaginary + c2.imaginary;
	return (tmp);
}

void	ft_fractal(void (*f)(t_vars*), t_vars *vars)
{
	f(vars);
}

int ft_complex_sqrnorm(t_complex c)
{
	int a;
	int b;

	a = c.real * c.real;
	b = c.imaginary * c.imaginary;
	return (a + b);
}

t_complex ft_complex_mult(t_complex c1, t_complex c2)
{
	t_complex	tmp;

	tmp.real = c1.real * c2.real - c1.imaginary * c2.imaginary;
	tmp.imaginary = c1.real * c2.imaginary + c2.real * c1.imaginary;
	
	return (tmp);
}

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
		z = ft_complex_mult(z, z);
		z = ft_complex_add(z, c);
		if (ft_complex_sqrnorm(z) > 4 * vars->smooth)
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
	double x;
	double y;
	double	point_x;
	double	point_y;
	int 	iter;
	double	k;
	t_data img_id;

	clock_t begin = clock();
	k = 2.0 * vars->zoom;
	x = 0.0;
	img_id = vars->img;
	while (x < 1.0)
	{
		y = 0.0;
		while (y < 1.0) 
		{
			point_x = ft_lerp(-k + vars->offset_x, k + vars->offset_x, x);
			point_y = ft_lerp(-k + vars->offset_y, k + vars->offset_y, y);
			iter = is_in_set(point_x, point_y, vars);
			if (!iter)
			{
				ft_mlx_pixel_put(&img_id, x * vars->window_data.width, y * vars->window_data.height, 0xFF000000);
			}
			else
				ft_mlx_pixel_put(&img_id, x * vars->window_data.width, y * vars->window_data.height, ft_color_hsv(fmod(iter * vars->iteration, 360), 1.0, 1.0));
			y+= 0.001 * vars->resolution;
		}
		x += 0.001 * vars->resolution;
	}
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("ft_mandelbrot= %f\n", time_spent);
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
	return (i);		
}

void ft_julia(t_vars *vars)
{
	double x;
	double y;
	double	point_x;
	double	point_y;
	int 	iter;
	double	k;

	clock_t begin = clock();
	k = 2.0 * vars->zoom;
	x = 0.0;
	while (x < 1.0)
	{
		y = 0.0;
		while (y < 1.0) 
		{
			point_x = ft_lerp(-k + vars->offset_x, k + vars->offset_x, x);
			point_y = ft_lerp(-k + vars->offset_y, k + vars->offset_y, y);
			iter = is_in_set_j(point_x, point_y, vars);
			ft_color(iter, x, y, vars);
			y+= 0.001 * vars->resolution;
		}
		x += 0.001 * vars->resolution;
	}
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("ft_julia 1 = %f\n", time_spent);
}

