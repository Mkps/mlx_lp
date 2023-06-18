#include "../minilibx/mlx.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct s_vars {
	void	*mlx;
	void	*window;
}	t_vars;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;
int	ft_mlx_close_window(int keycode, t_vars *vars)
{
	ft_printf("keycode is %i\n", keycode);
	if (keycode == 65307 || keycode == 27)
	{
		mlx_destroy_window(vars->mlx, vars->window);
		exit(0);
	}
	return (0);
}
int   create_argb(int a, int r, int g, int b)
{
  	return (a << 24 | r << 16 | g << 8 | b);
}
void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_line_aa(t_data *img, int x1, int y1, int x2, int y2)
{
	int m_new = 2 * (y2 - y1);
	int slope = m_new - (x2 - x1);
	for (int x = x1, y = y1; x <= x2; x++) {
		// if (y > y2)
		// 	y = y2;
		ft_printf("slope = %d, x = %d y = %d\n", slope, x, y);
		ft_mlx_pixel_put(img, x, y , 0x00FF0000);
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
void	ft_swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int ft_abs(int number)
{
	if (number >= 0)
		return (number);
	number *= -1;
	return (number);
}

void	ft_draw_line(t_data *img, int x0, int y0, int x1, int y1, int color);
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
		write(1, "steep\n", 6);
		printf("abs x %d abs y %d\n", ft_abs(x0 - x1), ft_abs(y0 - y1));
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
		ft_printf("x = %d y = %d slope = %d\n", x, y, (1 - ((x1 - x) / (x1 - x0))));
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

void ft_mlx_rect(t_data *img, int w, int h, int color)
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

void	ft_mlx_fill(t_data img, int size_x, int size_y, int color)
{
	int x;
  	int y;

	x = 0;
  	y = 0;
  	while (y < size_y)
  	{
    	x = 0;
		while(x < size_x)
		{
			ft_mlx_pixel_put(&img, x, y, color);
   			x++;
   		}
   		y++;
  	}
}
int	main(void)
{
	t_data	img;
	t_data  current;
	void	*mlx;
	void	*wnd;
	int		color;
	int		r;
	int		b;
	t_vars	vars;

	color = 0; 
	mlx = mlx_init();
	wnd = mlx_new_window(mlx, 640, 640, "mlx");
	img.img = mlx_new_image(mlx, 640, 640);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	current.img = mlx_new_image(mlx, 640, 640);
	current.addr = mlx_get_data_addr(current.img, &current.bits_per_pixel, &current.line_length, &current.endian);
	vars.mlx = mlx;
	vars.window = wnd;
	r = 255;
	b = 255;
	color = create_argb(0, r, 0, b);
	// draw_square(&img, 450, color);
	// draw_square(&current, 150, 0x00FF0000);
	ft_mlx_fill(img, 640, 640, 0xFFFFFFFF);
	// ft_draw_line(&img, 200, 200, 300, 300, color);
	// ft_draw_line(&img, 100, 300, 200, 200, color);
	ft_draw_line_thick(&img, 100, 300, 300, 300, color, 6);
	draw_triangle(&img, 300, 300, 150, 0xFFFF0000);
	mlx_put_image_to_window(mlx, wnd, img.img, 0, 0);
	printf("color = %d\n", color);
	mlx_hook(vars.window, 2, 1L<<0, ft_mlx_close_window, &vars);
	mlx_loop(mlx);
	return (0);
}
