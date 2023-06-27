#include "../includes/mlx_lp.h"

void	ft_swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

double	ft_lerp(double a, double b, double t)
{
	return (a + t * (b - a));
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
int	ft_is_in_set(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}
void ft_menu(t_vars *vars)
{
	int x;
	int	color;

	x = vars->window_data.width / 20;
	if (vars->color >= 0 && vars->color <= 3)
		color = 0xFFFFFFFF;
	else
		color = 0xFF000000;
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
			"Increase/Decrease current iteration : [U] [J]");
	mlx_string_put(vars->mlx, vars->w_ptr, x, 195, color,
			"Exit : [ESCAPE]");
}

void	ft_fractal(void (*f)(t_vars*), t_vars *vars)
{
	f(vars);
}

double	ft_atof(char *str)
{
	int		sign;
	int		decimal;
	int		i;
	double	result;

	i = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = 0;
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		i++;
	decimal = 0;
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
		decimal++;
	}
	while (decimal)
	{
		result /= 10.0;
		decimal--;
	}
	result *= sign;
	if (str[i] != 0)
	{
		ft_putstr_fd("Incorrect parameter: ", 2);
		ft_putendl_fd(str, 2);
		exit (1);
	}
	return (result);
}
