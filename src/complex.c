#include "../includes/mlx_lp.h"

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

t_complex ft_complex_div(t_complex c1, t_complex c2)
{
	t_complex	ret;

	ret.real = (c1.real * c2.real + c1.imaginary * c2.imaginary) / (c2.real * c2.real + c2.imaginary * c2.imaginary);
	ret.imaginary = (-c1.real * c2.imaginary + c1.imaginary * c2.real) / (c2.real * c2.real + c2.imaginary * c2.imaginary);
	return (ret);
}
t_complex ft_complex_add(t_complex c1, t_complex c2)
{
	t_complex tmp;

	tmp.real = c1.real + c2.real;
	tmp.imaginary = c1.imaginary + c2.imaginary;
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

