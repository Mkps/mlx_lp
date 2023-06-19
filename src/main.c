#include "../includes/mlx_lp.h"


int	main(int argc, char **argv)
{
	// t_data	img;
	// void	*mlx;
	// void	*wnd;
	int	WIDTH;
	int	HEIGHT;
	// int		color;
	// int		r;
	// int		b;
	t_vars	vars;
	t_data	img;
	WIDTH = 1000;
	HEIGHT = 1000;
	vars.mlx = mlx_init();
	vars.window = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "mlx");
	img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	vars.img = img;
	if (argc == 1)
	{
		img.zoom = 1.0;
		img.offset = 0.0;
	}
	else 
	{
		img.zoom = (float)ft_atoi(argv[1])/100;
		img.offset = (float)ft_atoi(argv[2])/100;
	}
	vars.c.real = 0.403333;
	vars.c.imaginary = 0.273333;
	// vars.mlx = mlx;
	// vars.window = wnd;
	// vars.img = &img;
	// r = 255;
	// b = 255;
	// color = create_argb(255, r, 0, b);
	// draw_rect(vars.img->img, 450, 450, 0xFFFF0000);
	// draw_square(&current, 150, 0x00FF0000);
	// ft_mlx_fill(img, 40, 640, 0xFFFF0000);
	// ft_draw_line(&img, 200, 200, 300, 300, color);
	// ft_draw_line(&img, 100, 300, 200, 200, color);
	// ft_draw_line_thick(&img, 100, 300, 300, 300, color, 6);
	// draw_triangle(vars.img->img, 300, 300, 150, 0xFFFF0000);
	// ft_mandelbrot(&img, WIDTH, HEIGHT);	
		
	ft_julia(img, WIDTH, HEIGHT, vars.c);
	mlx_put_image_to_window(vars.mlx, vars.window, vars.img.img, 0, 0);
	// // mlx_string_put(vars.mlx, vars.window, WIDTH / 3, HEIGHT / 20, 0xFFFFFFFF, "*** Mandelbrot ***");
	mlx_hook(vars.window, 2, 1L<<0, ft_mlx_key_hook, &vars);
	mlx_hook(vars.window, 17, 0, ft_mlx_destroy_hook, &vars); 
	mlx_loop(vars.mlx);
	return (0);
}
