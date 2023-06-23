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

t_complex ft_complex_add(t_complex c1, t_complex c2)
{
	t_complex tmp;

	tmp.real = c1.real + c2.real;
	tmp.imaginary = c1.imaginary + c2.imaginary;
	return (tmp);
}

void	ft_fractal(void (*f)(t_vars*), t_vars *vars)
{
	f(vars);
}

double	ft_complex_sqrnorm(t_complex c)
{
	double	a;
	double	b;

	a = c.real * c.real;
	b = c.imaginary * c.imaginary;
	return (a + b);
}

t_complex ft_complex_mult(t_complex c1, t_complex c2)
{
	t_complex	tmp;

	tmp.real = c1.real * c2.real - c1.imaginary * c2.imaginary;
	tmp.imaginary = c1.real * c2.imaginary + c2.real * c1.imaginary;
	
	return (tmp);
}

t_complex ft_complex_sub(t_complex c1, t_complex c2)
{
	t_complex tmp;

	tmp.real = c1.real - c2.real;
	tmp.imaginary = c1.imaginary - c2.imaginary;
	return (tmp);
}

t_complex ft_complex_pow(t_complex c1, int pow)
{
	t_complex tmp;

	if (pow <= 0)
	{
		tmp.real = 1;
		tmp.imaginary = 0;
	}
	if (pow == 1)
		return (c1);
	tmp = c1;
	pow--;
	while (pow)
	{
		tmp = ft_complex_mult(tmp, c1);
		pow--;
	}
	return (tmp);
}
