#include "../includes/mlx_lp.h"

t_complex	ft_nova_calc(t_complex c, t_complex z)
{
	t_complex	z_num;
	t_complex	z_den;
	t_complex	o;
	t_complex	inv;

	o = z;
	z_num = ft_complex_create(ft_complex_pow(z, 3).r - 1, 
			ft_complex_pow(z, 3).i);
	z_den = ft_complex_create(3 * ft_complex_pow(z, 2).r, 
			3 * ft_complex_pow(z, 2).i);
	inv = ft_complex_create(z_den.r, z_den.i * -1);
	z_num = ft_complex_mult(z_num, inv);
	z_den = ft_complex_mult(z_den, inv);
	z.r = z_num.r / z_den.r;
	z.i = z_num.i / z_den.r;
	z.r = o.r - z.r + c.r;
	z.i = o.i - z.i + c.i;
	return (z);
}

int	is_in_set_n(double x, double y, t_vars *vars)
{
	t_complex	z;
	t_complex	c;
	t_complex	o;
	int			i;

	z = ft_complex_create(1, 0);
	c = ft_complex_create(x, y);
	i = 1;
	while (i < vars->iteration)
	{
		o = z;
		z = ft_nova_calc(c, z);
		if ((fabs(z.r - o.r) < 0.0000000001 && 
				fabs(z.i - o.i) < 0.0000000001)
			|| ft_complex_sqrnorm(z) > 4.0)
			return (i * ft_complex_sqrnorm(z));
		i++;
	}
	return (i * ft_complex_sqrnorm(z));
}

void	ft_nova(t_vars *vars)
{
	t_coord	s;
	t_coord	p;
	double	screen_ratio;
	int		iter;
	double	k;

	screen_ratio = (float)vars->w_data.width / vars->w_data.height;
	k = 2.0 * vars->zoom;
	s.x = 0.0;
	while (s.x < 1.0)
	{
		s.y = 0.0;
		while (s.y < 1.0) 
		{
			p.x = ft_lerp(-k * screen_ratio + vars->offset_x, 
					k * screen_ratio + vars->offset_x, s.x);
			p.y = ft_lerp(-k + vars->offset_y, k + vars->offset_y, s.y);
			iter = is_in_set_n(p.x, p.y, vars);
			ft_color(iter, s.x, s.y, vars);
			s.y += 0.001 * vars->resolution;
		}
		s.x += 0.001 * vars->resolution;
	}
}

int	is_in_set_ship(double x, double y, t_vars *vars)
{
	int			i;
	t_complex	z;
	t_complex	c;
	t_complex	tmp;

	i = 1;
	c = ft_complex_create(x, y);
	z = ft_complex_create(0.0, 0.0);
	while (i <= vars->iteration)
	{
		tmp.r = fabs(z.r);
		tmp.i = fabs(z.i);
		z = ft_complex_pow(tmp, vars->power);
		z = ft_complex_add(z, c);
		if (ft_complex_sqrnorm(z) > 4)
			return (i);
		i++;
	}
	return (0);
}

void	ft_burning_ship(t_vars *vars)
{
	t_coord	s;
	t_coord	p;
	double	screen_ratio;
	int		iter;
	double	k;

	screen_ratio = (float)vars->w_data.width / vars->w_data.height;
	k = 2.0 * vars->zoom;
	s.x = 0.0;
	while (s.x < 1.0)
	{
		s.y = 0.0;
		while (s.y < 1.0) 
		{
			p.x = ft_lerp(-k * screen_ratio + vars->offset_x, 
					k * screen_ratio + vars->offset_x, s.x);
			p.y = ft_lerp(-k + vars->offset_y, k + vars->offset_y, s.y);
			iter = is_in_set_ship(p.x, p.y, vars);
			ft_color(iter, s.x, s.y, vars);
			s.y += 0.001 * vars->resolution;
		}
		s.x += 0.001 * vars->resolution;
	}
}
