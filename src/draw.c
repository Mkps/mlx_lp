#include "../includes/mlx_lp.h"

void	draw_line_old(t_data *img, int x1, int y1, int x2, int y2)
{
	int m_new = 2 * (y2 - y1);
	(void)img;
	int slope = m_new - (x2 - x1);
	for (int x = x1, y = y1; x <= x2; x++) {
		// if (y > y2)
		// 	y = y2;
		slope += m_new;
		if (slope > 0) {
			y++;
			slope -= 2 * (x2 - x1);
		}
		else if (slope < 0) {
			y--;
			slope += 2 * (x2 - x1);
		}
	}
}

void	ft_draw_line_thick(t_data *img, int x0, int y0, int x1, int y1, int color, int thickness)
{
	while (thickness--)
	{
		ft_draw_line(img, x0, y0++, x1, y1++, color);
	}
}

void	ft_draw_line(t_data *img, int x0, int y0, int x1, int y1, int color)
{
	int	x;
	int	y;
	float slope;
	int	steep;

	steep = 0;
	slope = 0;
	if (ft_abs(x0 - x1) < ft_abs(y0 - y1))
	{
		steep = 1;
		ft_swap(&x0, &y0);
		ft_swap(&x1, &y1);
	}
	if (x0 > x1)
	{
		ft_swap(&x0, &x1);
		ft_swap(&y0, &y1);
	}
	x = x0;
	y = y0;
	while (x < x1)
	{ 
		slope = (x - x0) / (float)(x1 - x0);
		y = y0 + (y1 - y0) * slope;
		if (!steep)
			ft_mlx_pixel_put(img, x, y, color);
		else
			ft_mlx_pixel_put(img, y, x, color);
		x++;
	}
}
void draw_triangle(t_data *img, int x, int y, int size, int color)
{
	ft_draw_line(img, x, y, x + size, y, color);
	ft_draw_line(img, x, y , x + size / 2, y + size, color);
	ft_draw_line(img, x + (size / 2), y + size, x + size, y, color);

}

void draw_rect(t_data *img, int w, int h, int color)
{
  int x;
  int y;

  x = 0;
  y = 0;
  while (y < h)
  {
    x = 0;
    while(x < w)
    {
    	ft_mlx_pixel_put(img, x, y, color);
      	x++;
    }
    y++;
  }
}

int   ft_color_argb(t_argb argb)
{
  	return (argb.a << 24 | argb.r << 16 | argb.g << 8 | argb.b);
}
int   ft_color_int(int a, int r, int g, int b)
{
  	return (a << 24 | r << 16 | g << 8 | b);
}

int ft_color_hsv(double H, double s, double v)
{
	t_hsv t2;
	t_hsv ret;
	t_argb rgb;

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
	else if(H >= 120 && H < 180)
	{
		ret.h = 0;
		ret.s = t2.h;
		ret.v = t2.v;
	}
	else if(H >= 180 && H < 240)
	{
		ret.h = 0;
		ret.s = t2.v;
		ret.v = t2.h;
	}
	else if(H >= 240 && H < 300)
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
	return(ft_color_argb(rgb));
}
void	ft_color(int iter, double x, double y, t_vars *vars)
{
	t_data img;
	int in_set;

	img = vars->img;
	x *= vars->window_data.width;
	y *= vars->window_data.height;
	in_set = 0xFF000000;
	if (iter >= vars->iteration)
	{
		ft_mlx_pixel_put(&img, x, y, in_set);
		return ;
	}
	if (iter % 2 == 0)
		ft_mlx_pixel_put(&img, x, y, 0xFFFFFFFF);
	else
		ft_mlx_pixel_put(&img, x, y , ft_color_int(255, (3 * iter) % 255, (3 * iter) % 255, (3 * iter) % 255));
	// if (iter < 80)
	// 	ft_mlx_pixel_put(&img, x, y, ft_color_int(255, 177, 0, 0));
	// else
	// 	ft_mlx_pixel_put(&img, x, y, ft_color_int(255, 255, 225, 140));
	// ft_mlx_pixel_put(&img, x, y, ft_color_hsv(3 * iter * vars->iteration % 360, 1.0, 1.0));
}


