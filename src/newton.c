#include "../includes/mlx_lp.h"

t_complex ft_newton_f(t_complex c)
{
	t_complex	tmp;

	tmp = ft_complex_pow(c, 3);
	tmp = ft_complex_sub(tmp, ft_complex_create(1.0, 0.0));
	return (tmp);
}

t_complex	ft_newton_df(t_complex c)
{
	t_complex	tmp;

	tmp = ft_complex_pow(c, 2);
	tmp.real = tmp.real * 3.0;
	tmp.imaginary = tmp.imaginary * 3.0;
	return (tmp);
}

int is_in_set_newton(double x, double y, t_vars *vars)
{
	int			i;
	t_complex	z;
	t_complex	z_num;
	t_complex	z_den;
	t_complex	o;
	// t_complex	inv;

	z.real = x;
	z.imaginary = y;
	i = 1;
	while (i < vars->iteration)
	{
		o = z;
		z_num = ft_newton_f(z);
		z_den = ft_newton_df(z);
		z = ft_complex_div(z_num, z_den);
		z.real = o.real - z.real;
		z.imaginary = o.imaginary - z.imaginary; 
		if (fabs(z.real - o.real) < 0.00000001 && fabs(z.imaginary - o.imaginary) < 0.00000001)
			return (trunc(ft_complex_arg(z)));
		i++;
	}
	return (trunc(ft_complex_arg(z)));
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
