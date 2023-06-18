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


