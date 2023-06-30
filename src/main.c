#include "../includes/mlx_lp.h"

void	ft_vars_init(t_vars *vars)
{
	vars->w_data.width = 1000;
	vars->w_data.height = 1000;
	vars->mlx = mlx_init();
	vars->w_ptr = mlx_new_window(vars->mlx, vars->w_data.width, 
			vars->w_data.height, "fractol");
	init_img(vars);
	if (vars->fractal == ft_nova)
		vars->offset_x = -1.0;
	else
		vars->offset_x = 0.0;
	vars->offset_y = 0.0;
	vars->resolution = ((float)vars->w_data.height / vars->w_data.width);
	if (vars->w_data.width >= vars->w_data.height)
		vars->resolution = ((float)vars->w_data.height / vars->w_data.width);
	else
		vars->resolution = ((float)vars->w_data.width / vars->w_data.height);
	vars->iteration = 256;
	vars->smooth = 1;
	vars->is_menu_on = 0;
	vars->zoom = 1.0;
}

void	ft_fractal_defaults(t_vars *vars)
{
	if (vars->fractal == ft_mandelbrot)
		vars->color = 0;
	else if (vars->fractal == ft_julia)
		vars->color = 2;
	else if (vars->fractal == ft_power)
	{
		vars->color = 7;
		vars->power = 4;
	}
	else if (vars->fractal == ft_newton)
		vars->color = 9;
	else if (vars->fractal == ft_nova)
	{
		vars->color = 3;
		vars->offset_x = -1;
	}
	else if (vars->fractal == ft_burning_ship)
	{
		vars->color = 0;
		vars->power = 2;
	}
}

void	ft_fractal_init(char *fractal, t_vars *vars)
{
	if (!ft_strncmp(fractal, "Mandelbrot", ft_strlen("Mandelbrot")))
		vars->fractal = ft_mandelbrot;
	else if (!ft_strncmp(fractal, "Julia", ft_strlen("Julia")))
	{
		vars->fractal = ft_julia;
		vars->c = ft_complex_create(-0.77146, -0.10119);
	}
	else if (!ft_strncmp(fractal, "Power", ft_strlen("Power")))
		vars->fractal = ft_power;
	else if (!ft_strncmp(fractal, "Newton", ft_strlen("Newton")))
		vars->fractal = ft_newton;
	else if (!ft_strncmp(fractal, "Nova", ft_strlen("Nova")))
		vars->fractal = ft_nova;
	else if (!ft_strncmp(fractal, "BurningShip", ft_strlen("BurningShip")))
		vars->fractal = ft_burning_ship;
	else
	{
		ft_putendl_fd("Invalid fractal name...", 2);
		ft_putstr_fd("Available fractals [Mandelbrot | Julia | Nova | ", 2);
		ft_putstr_fd("Newton | Power | BurningShip]\n", 2);
		exit(0);
	}
}

void	ft_arg_check(int argc, char **argv, t_vars *vars)
{
	if (argc < 2 || (!ft_strncmp(argv[1], "Julia", ft_strlen("Julia")) 
			&& (argc < 4 && argc != 2)))
	{
		ft_putstr_fd("Error too few arguments.\n", 2);
		ft_putstr_fd("Use with \"./fractol [Fractal Name]\" or ", 2);
		ft_putstr_fd("\" ./fractol [Julia] [real] [imaginary]\"\n", 2);
		exit (0);
	}
	if (argc > 4 || (ft_strncmp(argv[1], "Julia", ft_strlen("Julia")) 
			&& argc > 2))
	{
		ft_printf("Error too many arguments.\n");
		ft_putstr_fd("Use with \"./fractol [Fractal Name]\" or ", 2);
		ft_putstr_fd("\" ./fractol [Julia] [real] [imaginary]\"\n", 2);
		exit (0);
	}
	if (argc == 2)
		ft_fractal_init(argv[1], vars);
	if (argc == 4 && !ft_strncmp(argv[1], "Julia", ft_strlen("Julia")))
	{
		ft_fractal_init(argv[1], vars);
		vars->c.r = ft_atof(argv[2]);
		vars->c.i = ft_atof(argv[3]);
	}
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	ft_arg_check(argc, argv, &vars);
	ft_vars_init(&vars);
	ft_fractal_defaults(&vars);
	ft_fractal(vars.fractal, &vars);
	mlx_put_image_to_window(vars.mlx, vars.w_ptr, vars.img.img, 0, 0);
	ft_menu(&vars);
	mlx_mouse_hook(vars.w_ptr, ft_mlx_mouse_hook, &vars);
	mlx_hook(vars.w_ptr, 2, 1L << 0, ft_mlx_key_hook, &vars);
	mlx_hook(vars.w_ptr, 17, 0, ft_mlx_destroy_hook, &vars); 
	mlx_loop_hook(vars.mlx, ft_mlx_render, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
