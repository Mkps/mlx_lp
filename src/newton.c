#include "../includes/mlx_lp.h"

t_complex	ft_newton_f(t_complex c)
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
	tmp.r = tmp.r * 3.0;
	tmp.i = tmp.i * 3.0;
	return (tmp);
}

int	is_in_set_newton(double x, double y, t_vars *vars)
{
	int			i;
	t_complex	z;
	t_complex	z_num;
	t_complex	z_den;
	t_complex	o;

	z.r = x;
	z.i = y;
	i = 1;
	while (i < vars->iteration)
	{
		o = z;
		z_num = ft_newton_f(z);
		z_den = ft_newton_df(z);
		z = ft_complex_div(z_num, z_den);
		z.r = o.r - z.r;
		z.i = o.i - z.i; 
		if (fabs(z.r - o.r) < 0.00000001 && fabs(z.i - o.i) < 0.00000001)
			return (trunc(ft_complex_arg(z)));
		i++;
	}
	return (trunc(ft_complex_arg(z)));
}

void	ft_newton(t_vars *vars)
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
			iter = is_in_set_newton(p.x, p.y, vars);
			ft_color(iter, s.x, s.y, vars);
			s.y += 0.001 * vars->resolution;
		}
		s.x += 0.001 * vars->resolution;
	}
}
