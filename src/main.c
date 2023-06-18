#include "../includes/mlx_lp.h"


int	main(void)
{
	t_data	img;
	void	*mlx;
	void	*wnd;
	int	WIDTH;
	int	HEIGHT;
	// int		color;
	// int		r;
	// int		b;
	t_vars	vars;
	WIDTH = 1000;
	HEIGHT = 1000;
	mlx = mlx_init();
	wnd = mlx_new_window(mlx, WIDTH, HEIGHT, "mlx");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	vars.mlx = mlx;
	vars.window = wnd;
	// r = 255;
	// b = 255;
	// color = create_argb(255, r, 0, b);
	// draw_square(&img, 450, color);
	// draw_square(&current, 150, 0x00FF0000);
	// ft_mlx_fill(img, 40, 640, 0xFFFFFFFF);
	// ft_draw_line(&img, 200, 200, 300, 300, color);
	// ft_draw_line(&img, 100, 300, 200, 200, color);
	// ft_draw_line_thick(&img, 100, 300, 300, 300, color, 6);
	// draw_triangle(&img, 300, 300, 150, 0xFFFF0000);
	ft_mandelbrot(&img, WIDTH, HEIGHT);	
	mlx_put_image_to_window(mlx, wnd, img.img, 0, 0);
	mlx_string_put(vars.mlx, vars.window, WIDTH / 3, HEIGHT / 20, 0xFFFFFFFF, "*** Mandelbrot ***");
	mlx_hook(vars.window, 2, 1L<<0, ft_mlx_close_window, &vars);
	mlx_loop(mlx);
	return (0);
}
