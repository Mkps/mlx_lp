#include "../includes/mlx_lp.h"
#include <math.h>
t_complex ft_complex_add(t_complex c1, t_complex c2)
{
	t_complex tmp;

	tmp.real = c1.real + c2.real;
	tmp.imaginary = c1.imaginary + c2.imaginary;
	return (tmp);
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

int is_in_set(double x, double y)
{
	t_complex	z;
	t_complex	c;
	int			i;

	c.real = x;
	c.imaginary = y;
	z.real = 0;
	z.imaginary = 0;
	i = 1;
	while (i < 250)
	{
		z = ft_complex_mult(z, z);
		z = ft_complex_add(z, c);
		if (ft_complex_sqrnorm(z) > 25)
			return (i);
		i++;
	}
	return (0);
}

double	ft_lerp(double a, double b, double t)
{
	return (a + t * (b - a));
}
void ft_mandelbrot(t_data *img, int width, int height)
{
	double x;
	double y;
	double	point_x;
	double	point_y;
	int iter;
	// float k;

	// k = 1 / (float)width;
	// (void)height;
	x = 0.0;
	while (x < 1.0)
	{
		y = 0.0;
		while (y < 1.0) 
		{
			point_x = ft_lerp(-2.0, 2.0, x);
			point_y = ft_lerp(-2.0, 2.0, y);
			iter = is_in_set(point_x, point_y);
			if (!iter)
			{
				ft_mlx_pixel_put(img, x * width, y * height, 0xFF000000);
			}
			else
				ft_mlx_pixel_put(img, x * width, y * height, create_argb(255, 3 * iter % 255, 3 * iter % 255, 3 * iter % 255));
			y+= 0.0005;
		}
		x += 0.0005;
	}
}

int is_in_set_j(double x, double y)
{
	t_complex	z;
	t_complex	c;
	int			i;

	c.real = -0.7;
	c.imaginary = 0.27015;
	z.real = x;
	z.imaginary = y;
	i = 1;
	while (i < 250)
	{
		z = ft_complex_mult(z, z);
		z = ft_complex_add(z, c);
		if (ft_complex_sqrnorm(z) > 4)
			return (i);
		i++;
	}
	return (0);
}

void ft_julia(t_data *img, int width, int height)
{
	double x;
	double y;
	double	point_x;
	double	point_y;
	int 	iter;
	double	k;

	k = 1.0 * img->zoom;
	x = 0.0;
	while (x < 1.0)
	{
		y = 0.0;
		while (y < 1.0) 
		{
			point_x = ft_lerp(-k + img->offset, k + img->offset, x);
			point_y = ft_lerp(-k, k, y);
			iter = is_in_set_j(point_x, point_y);
			if (!iter)
			{
				ft_mlx_pixel_put(img, x * width, y * height, 0xFF000000);
			}
			else
				ft_mlx_pixel_put(img, x * width, y * height, create_argb(255, 0, 3 * iter % 255, 3 * iter % 255));
			y+= 0.001;
		}
		x += 0.001;
	}

}
