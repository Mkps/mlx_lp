#ifndef MLX_LP_H
# define MLX_LP_H

# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <time.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	float	zoom;
	float	offset;
}				t_data;

typedef struct s_complex {
	double	real;
	double	imaginary;
}	t_complex;

typedef struct s_vars {
	void	*mlx;
	void	*window;
	t_complex c;
	t_data	img;
}	t_vars;

int		ft_mlx_close_window(int keycode, t_vars *vars);
int		ft_mlx_destroy_hook(t_vars *vars);
void	ft_mlx_fill(t_data img, int size_x, int size_y, int color);
int   create_argb(int a, int r, int g, int b);
void	ft_mlx_pixel_put(t_data *data, int x, int y, int color);
void	ft_swap(int *a, int *b);
int ft_abs(int number);
void	ft_draw_line_thick(t_data *img, int x0, int y0, int x1, int y1, int color, int thickness);
void	ft_draw_line(t_data *img, int x0, int y0, int x1, int y1, int color);
void draw_triangle(t_data *img, int x, int y, int size, int color);
void draw_rect(t_data *img, int w, int h, int color);
void ft_mandelbrot(t_data *img, int w, int h);
void	ft_julia(t_data img, int w, int h, t_complex c);
int		ft_mlx_key_hook(int keycode, t_vars *vars);

#endif
