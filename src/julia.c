#include "../includes/mlx_lp.h"

int	is_in_set_j(double x, double y, t_vars *vars)
{
	t_complex	z;
	int			i;
	double		t;

	z.r = x;
	z.i = y;
	t = 0;
	i = 1;
	while (i < vars->iteration)
	{
		t = z.r;
		z.r = t * t - z.i * z.i + vars->c.r;
		z.i = 2 * z.i * t + vars->c.i;
		if (ft_complex_sqrnorm(z) > 4 * vars->smooth)
			return (i);
		i++;
	}
	return (0);
}

void	ft_julia(t_vars *vars)
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
		while (y < 1.0) 
		{
			p.x = ft_lerp(-k * screen_ratio + vars->offset_x, 
					k * screen_ratio + vars->offset_x, s.x);
			p.y = ft_lerp(-k + vars->offset_y, k + vars->offset_y, s.y);
			iter = is_in_set_j(p.x, p.y, vars);
			ft_color(iter, s.x, s.y, vars);
			y += 0.001 * vars->resolution;
		}
		x += 0.001 * vars->resolution;
	}
}
