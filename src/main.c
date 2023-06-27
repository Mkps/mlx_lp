#include "../includes/mlx_lp.h"
void	ft_vars_init(t_vars *vars)
{
	vars->window_data.width = 1000;
	vars->window_data.height = 1000;
	vars->mlx = mlx_init();
	vars->w_ptr = mlx_new_window(vars->mlx, vars->window_data.width, vars->window_data.height, "fractol");
	init_img(vars);
	if (vars->fractal == ft_nova)
		vars->offset_x = -1.0;
	else
		vars->offset_x = 0.0;
	vars->offset_y = 0.0;
	vars->resolution = ((float)vars->window_data.height / vars->window_data.width);
	printf("resolution = %f\n", vars->resolution);
	if (vars->window_data.width >= vars->window_data.height)
		vars->resolution = ((float)vars->window_data.height / vars->window_data.width);
	else
		vars->resolution = ((float)vars->window_data.width / vars->window_data.height);
	vars->iteration = 256;
	vars->smooth = 1;
	vars->is_menu_on = 0;
	vars->zoom = 1.0;
}

void	ft_fractal_init(char *fractal, t_vars *vars)
{
	if (!ft_strncmp(fractal, "Mandelbrot", ft_strlen(fractal)))
	{
		vars->color = 0;
		vars->fractal = ft_mandelbrot;
	}
	else if (!ft_strncmp(fractal, "Julia", ft_strlen(fractal)))
	{
		vars->color = 2;
		vars->c = ft_complex_create(-0.77146, -0.10119);
		vars->fractal = ft_julia;
	}
	else if (!ft_strncmp(fractal, "Power", ft_strlen(fractal)))
	{
		vars->color = 7;
		vars->power = 4;
		vars->fractal = ft_power;
	}
	else if (!ft_strncmp(fractal, "Newton", ft_strlen(fractal)))
	{
		vars->color = 9;
		vars->fractal = ft_newton;
	}
	else if (!ft_strncmp(fractal, "Nova", ft_strlen(fractal)))
	{
		vars->color = 3;
		vars->offset_x = -1;
		vars->fractal = ft_nova;
	}
	else if (!ft_strncmp(fractal, "BurningShip", ft_strlen(fractal)))
	{
		vars->color = 0;
		vars->power = 2;
		vars->fractal = ft_burning_ship;
	}
	else
	{
	 	ft_printf("Invalid fractal name...\nAvailable fractals are [ Mandelbrot | Julia | Nova | Newton | Power | BurningShip]\n");
		exit(0);
	}
}
void	ft_arg_check(int argc, char **argv, t_vars *vars)
{
	if (argc < 2)
	{
		ft_printf("Error too few arguments.\n Use with \"./fractol [Fractal Name]\"\n");
		exit (0);
	}

	if (argc > 4 || argc == 3)
	{
		ft_printf("Error too many arguments.\n Use with \"./fractol [Fractal Name]\" or \" ./fractol [Julia] [real value] [imaginary value]\n");
		exit (0);
	}
	if (argc == 2)
	{
		ft_fractal_init(argv[1], vars);
	}
	if (argc == 4 && !ft_strncmp(argv[1], "Julia", ft_strlen(argv[1])))
	{
		vars->c.real = ft_atof(argv[2]);
		vars->c.imaginary = ft_atof(argv[3]);
	}

}
int	main(int argc, char **argv)
{
	t_vars	vars;

	ft_arg_check(argc, argv, &vars);
	ft_vars_init(&vars);
	ft_fractal(vars.fractal, &vars);
	mlx_put_image_to_window(vars.mlx, vars.w_ptr, vars.img.img, 0, 0);
	ft_menu(&vars);
	mlx_hook(vars.w_ptr, 2, 1L<<0, ft_mlx_key_hook, &vars);
	mlx_hook(vars.w_ptr, 17, 0, ft_mlx_destroy_hook, &vars); 
	mlx_loop(vars.mlx);
	return (0);
}
