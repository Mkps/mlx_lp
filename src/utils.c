#include "../includes/mlx_lp.h"

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

float ft_fabs(float number)
{
	if (number >= 0)
		return (number);
	number *= -1;
	return (number);
}

void ft_menu(t_vars *vars)
{
	int x;
	int	color;

	x = vars->window_data.width / 20;
	color = 0xFFFFFFFF;
	if (vars->is_menu_on == 0)
	{
		mlx_string_put(vars->mlx, vars->w_ptr, x, 10, color,
				"Press 'H' to open menu");
		return ;

	}
	mlx_string_put(vars->mlx, vars->w_ptr, x, 10, color,
			"Press 'H' to close menu");
	mlx_string_put(vars->mlx, vars->w_ptr, x, 35, color,
			"Move around with : [W][A][S][D]");
	mlx_string_put(vars->mlx, vars->w_ptr, x, 60, color,
			"Zoom : [Mouse wheel or [Z]/[X]]");
	mlx_string_put(vars->mlx, vars->w_ptr, x, 85, color,
			"Change Fractal : [1, 2, ...]");
	mlx_string_put(vars->mlx, vars->w_ptr, x, 110, color,
			"Change Color : [TAB] || L-Mouse R-Mouse");
	mlx_string_put(vars->mlx, vars->w_ptr, x, 135, color,
			"Increase/Decrease current iteration : [+] [-]");
	mlx_string_put(vars->mlx, vars->w_ptr, x, 195, color,
			"Exit : [ESCAPE]");
}

void	ft_fractal(void (*f)(t_vars*), t_vars *vars)
{
	f(vars);
}


