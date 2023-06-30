#include "../includes/mlx_lp.h"
#include <inttypes.h>

double	ft_complex_sqrnorm(t_complex c)
{
	double	a;
	double	b;

	a = c.r * c.r;
	b = c.i * c.i;
	return (a + b);
}

t_complex ft_complex_mult(t_complex c1, t_complex c2)
{
	t_complex	tmp;

	tmp.r = c1.r * c2.r - c1.i * c2.i;
	tmp.i = c1.r * c2.i + c2.r * c1.i;
	
	return (tmp);
}

t_complex ft_complex_inv(t_complex num, t_complex den)
{
	t_complex	inv;
	t_complex	ret;

	inv.r = den.r;
	inv.i = den.i * -1;
	num = ft_complex_mult(num, inv);
	den = ft_complex_mult(den, inv);
	ret.r = 0;
	ret.i = 0;
	if (den.r != 0)
	{
	ret.r = num.r / den.r;
	ret.i = num.i / den.r;
	}
	return (ret);
}

t_complex ft_complex_div(t_complex c1, t_complex c2)
{
	t_complex	ret;

	ret.r = (c1.r * c2.r + c1.i * c2.i) / (c2.r * c2.r + c2.i * c2.i);
	ret.i = (-1 * c1.r * c2.i + c1.i * c2.r) / (c2.r * c2.r + c2.i * c2.i);
	return (ret);
}

t_complex ft_complex_add(t_complex c1, t_complex c2)
{
	t_complex tmp;

	tmp.r = c1.r + c2.r;
	tmp.i = c1.i + c2.i;
	return (tmp);
}
t_complex ft_complex_sub(t_complex c1, t_complex c2)
{
	t_complex tmp;

	tmp.r = c1.r - c2.r;
	tmp.i = c1.i - c2.i;
	return (tmp);
}

float	ft_complex_norm(t_complex c)
{
	return (c.r * c.r + c.i * c.i);
}
float	ft_complex_arg(t_complex c)
{
	return (atan2(c.i, c.r));
}

t_complex ft_complex_pow(t_complex c1, int pow)
{
	t_complex tmp;

	if (pow <= 0)
	{
		tmp.r = 1;
		tmp.i = 0;
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

t_complex ft_complex_create(double real, double imaginary)
{
	t_complex	ret;

	ret.r = real;
	ret.i = imaginary;
	return (ret);
}
