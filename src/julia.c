#include "../includes/mlx_lp.h"

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

