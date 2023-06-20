#include "../includes/mlx_lp.h"
void	ft_vars_init(t_vars *vars)
{
	vars->window_data.width = 800;
	vars->window_data.height = 600;
	vars->mlx = mlx_init();
	vars->w_ptr = mlx_new_window(vars->mlx, vars->window_data.width, vars->window_data.height, "mlx");
	init_img(vars);
	vars->offset_x = 0.0;
	vars->offset_y = 0.0;
	vars->c.real = 0.403333;
	vars->c.imaginary = 0.273333;
	vars->fractal = ft_mandelbrot;
	vars->resolution = 1.0;
	vars->iteration = 4;
	vars->smooth = 8;
	vars->is_menu_on = 0;
	vars->zoom = 1.0;
}


int	main(int argc, char **argv)
{
	t_vars	vars;
	(void)	argc;
	(void)	argv;
	
	ft_vars_init(&vars);
	ft_fractal(vars.fractal, &vars);
	mlx_put_image_to_window(vars.mlx, vars.w_ptr, vars.img.img, 0, 0);
	ft_menu(&vars);
	mlx_hook(vars.w_ptr, 2, 1L<<0, ft_mlx_key_hook, &vars);
	mlx_hook(vars.w_ptr, 17, 0, ft_mlx_destroy_hook, &vars); 
	mlx_loop(vars.mlx);
	return (0);
}
