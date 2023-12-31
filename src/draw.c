#include "../includes/mlx_lp.h"

int	ft_color_argb(t_argb argb)
{
	return (argb.a << 24 | argb.r << 16 | argb.g << 8 | argb.b);
}

int	ft_color_int(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

int	ft_color_hsv(double H, double s, double v)
{
	t_hsv	t2;
	t_hsv	ret;
	t_argb	rgb;

	t2.h = v * s;
	t2.s = v - t2.h;
	t2.v = t2.h * (1 - fabs(fmod((H / 60), 2)) - 1);
	if (H >= 0 && H < 60)
	{
		ret.h = t2.h;
		ret.s = t2.v;
		ret.v = 0;
	}
	else if (H >= 60 && H < 120)
	{
		ret.h = t2.v;
		ret.s = t2.h;
		ret.v = 0;
	}
	else if (H >= 120 && H < 180)
	{
		ret.h = 0;
		ret.s = t2.h;
		ret.v = t2.v;
	}
	else if (H >= 180 && H < 240)
	{
		ret.h = 0;
		ret.s = t2.v;
		ret.v = t2.h;
	}
	else if (H >= 240 && H < 300)
	{
		ret.h = t2.v;
		ret.s = 0;
		ret.v = t2.h;
	}
	else
	{
		ret.h = t2.h;
		ret.s = 0;
		ret.v = t2.v;
	}
	rgb.a = 255;
	rgb.r = trunc((ret.h + t2.s) * 255);
	rgb.g = trunc((ret.s + t2.s) * 255);
	rgb.b = trunc((ret.v + t2.s) * 255);
	return (ft_color_argb(rgb));
}

int	ft_color_br(t_vars *vars, int iter)
{
	double	s;

	(void)vars;
	s = (float)iter / 15;
	if (s > 1)
		s = 1.0;
	if (!iter)
		return (0xFF000000);
	return (ft_color_int(255, color_up(0, 223, s), 
			color_up(0, 0, s), color_up(0, 0, s)));
}

int	ft_color_cr(t_vars *vars, int iter)
{
	double	s;

	(void)vars;
	s = (float)iter / vars->iteration;
	if (s > 1)
		s = 1.0;
	if (!iter)
		return (0xFFFFFFFF);
	return (ft_color_int(255, color_up(255, 255, s), 
			color_up(255, 0, s), color_up(255, 0, s)));
}

int	ft_color_sin(t_vars *vars, int iter)
{
	iter = iter + 1 - (log(2) / vars->iteration) / log (2);
	if (!iter)
		return (0xFF000000);
	return (ft_color_int(255, 
			sin(0.116 * iter + 4) * 230 + 25, 
			sin(0.013 * iter + 2) * 255 + 25, 
			sin(0.01 * iter + 1) * 230 + 25));
}

int	ft_color_hue(int iter)
{
	double	iter_d;

	if (!iter)
		return (0xFF000000);
	iter_d = iter;
	return (ft_color_hsv(3 * iter % 255, 0.5 * sin(iter_d * 0.015) + 0.5, 1.0));
}

int	ft_color_bs(t_vars *vars, int iter)
{
	double	s;
	double	s2;

	s = (float)iter / 20;
	s2 = (float)(iter) / ((float)vars->iteration / 4);
	if (s > 1)
		s = 1.0;
	if (s2 > 1)
		s2 = 1.0;
	if (!iter)
		return (0xFF000000);
	if (iter < 20)
		return (ft_color_int(255, color_up(0, 255, s), 
				color_up(0, 230, s), color_up(30, 100, s)));
	return (ft_color_int(255, color_up(255, 255, s2), 
			color_up(255, 98, s2), color_up(100, 0, s2)));
}

int	ft_color_newton(int iter)
{
	if (!iter)
		return (ft_color_int(255, 0, 0, 255));
	else if (iter < 0)
		return (ft_color_int(255, 255, 0, 0));
	else
		return (ft_color_int(255, 0, 255, 0));
}

void	ft_color(int iter, double x, double y, t_vars *vars)
{
	t_data	img;

	img = vars->img;
	x *= vars->w_data.width;
	y *= vars->w_data.height;
	if (vars->color == 0)
		ft_mlx_pixel_put(&img, x, y, ft_color_bs(vars, iter));
	if (vars->color == 1)
		ft_mlx_pixel_put(&img, x, y, ft_color_bb(vars, iter));
	if (vars->color == 2)
		ft_mlx_pixel_put(&img, x, y, ft_color_ra(vars, iter));
	if (vars->color == 3)
		ft_mlx_pixel_put(&img, x, y, ft_color_sin(vars, iter));
	if (vars->color == 4)
		ft_mlx_pixel_put(&img, x, y, ft_color_hue(iter));
	if (vars->color == 5)
		ft_mlx_pixel_put(&img, x, y, ft_color_br(vars, iter));
	if (vars->color == 6)
		ft_mlx_pixel_put(&img, x, y, ft_color_cr(vars, iter));
	if (vars->color == 7)
		ft_mlx_pixel_put(&img, x, y, ft_color_mono(vars, iter));
	if (vars->color == 9)
		ft_mlx_pixel_put(&img, x, y, ft_color_newton(iter));
}
