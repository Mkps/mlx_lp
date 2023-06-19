#include "../includes/mlx_lp.h"


int	main(int argc, char **argv)
{
	// t_data	img;
	// void	*mlx;
	// void	*wnd;
	// int		color;
	// int		r;
	// int		b;
	t_vars	vars;
	// t_data	img;
	vars.window_data.width = 1000;
	vars.window_data.height = 1000;
	vars.mlx = mlx_init();
	vars.window_data.window_ptr = mlx_new_window(vars.mlx, vars.window_data.width, vars.window_data.height, "mlx");
	init_img(&vars);
	vars.offset_x = 0.0;
	vars.offset_y = 0.0;
	if (argc == 1)
		vars.zoom = 1.0;
	else 
		vars.zoom = (float)ft_atoi(argv[1])/100;
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
	// ft_mlx_fill(vars.img, vars.window_data.width, vars.window_data.height, 0xFFFF0000);
	// ft_draw_line(&img, 200, 200, 300, 300, color);
	// ft_draw_line(&img, 100, 300, 200, 200, color);
	// ft_draw_line_thick(&img, 100, 300, 300, 300, color, 6);
	// draw_triangle(vars.img->img, 300, 300, 150, 0xFFFF0000);
	// ft_mandelbrot(&img, WIDTH, HEIGHT);	
		
	ft_julia(&vars);
	mlx_put_image_to_window(vars.mlx, vars.window_data.window_ptr, vars.img.img, 0, 0);
	// // mlx_string_put(vars.mlx, vars.window, WIDTH / 3, HEIGHT / 20, 0xFFFFFFFF, "*** Mandelbrot ***");
	mlx_hook(vars.window_data.window_ptr, 2, 1L<<0, ft_mlx_key_hook, &vars);
	mlx_hook(vars.window_data.window_ptr, 17, 0, ft_mlx_destroy_hook, &vars); 
	mlx_loop(vars.mlx);
	return (0);
}
