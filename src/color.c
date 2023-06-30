#include "../includes/mlx_lp.h"

int	color_up(int c1, int c2, double s)
{
	double	t;
	int		ret;

	t = pow(s, 2);
	ret = round((1 - t) * c1 + t * c2);
	return (ret);
}

int	color_dn(int c1, int c2, double s)
{
	double	t;
	int		ret;

	t = 1 - pow(s, 2);
	ret = round((1 - t) * c1 + t * c2);
	return (ret); 
}

int	ft_color_ra(t_vars *vars, int iter)
{
	double	s;

	(void)vars;
	s = (float)iter / 40;
	if (s > 1)
		s = 1.0;
	if (!iter)
		return (0xFF000000);
	return (ft_color_int(255, color_up(130, 255, s),
			color_up(0, 225, s), color_up(0, 140, s)));
}

int	ft_color_mono(t_vars *vars, int iter)
{
	double	s;

	(void)vars;
	s = (float)iter / vars->iteration;
	if (s > 1)
		s = 1.0;
	if (!iter)
		return (0xFF000000);
	return (ft_color_int(255, color_up(255, 0, s), 
			color_up(255, 0, s), color_up(255, 0, s)));
}

int	ft_color_bb(t_vars *vars, int iter)
{
	double	s;

	(void)vars;
	s = (float)iter / 40;
	if (s > 1)
		s = 1.0;
	if (!iter)
		return (0xFF000000);
	return (ft_color_int(255, color_up(0, 225, s), 
			color_up(0, 225, s), color_up(30, 255, s)));
}
