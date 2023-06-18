#include "../includes/mlx_lp.h"

void	draw_line_old(t_data *img, int x1, int y1, int x2, int y2)
{
	int m_new = 2 * (y2 - y1);
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

