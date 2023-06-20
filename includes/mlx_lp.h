#ifndef MLX_LP_H
# define MLX_LP_H

# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <time.h>
# include <math.h>


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_complex {
	double	real;
	double	imaginary;
}	t_complex;

typedef struct s_window {
	void	*window_ptr;
	int	width;
	int	height;
}	t_window;
typedef struct s_vars {
	void	*fractal;
	void	*mlx;
	t_complex c;
	t_data	img;
	int		color;
	int		is_menu_on;
	int		smooth;
	float	zoom;
	float	resolution;
	int		iteration;
	float	offset_x;
	float	offset_y;
	t_window	window_data;
	
}	t_vars;

typedef struct s_argb {
	int	a;
	int	r;
	int g;
	int b;
} t_argb;

typedef struct s_hsv {
	double h;
	double s;
	double v;
}	t_hsv;
typedef void (* function_ptr)(t_vars*);

int		ft_mlx_close_window(int keycode, t_vars *vars);
int		ft_mlx_destroy_hook(t_vars *vars);
void	ft_mlx_fill(t_data img, int size_x, int size_y, int color);
void	ft_mlx_pixel_put(t_data *data, int x, int y, int color);
void	ft_swap(int *a, int *b);
int ft_abs(int number);
void	ft_draw_line_thick(t_data *img, int x0, int y0, int x1, int y1, int color, int thickness);
void	ft_draw_line(t_data *img, int x0, int y0, int x1, int y1, int color);
void draw_triangle(t_data *img, int x, int y, int size, int color);
void draw_rect(t_data *img, int w, int h, int color);
void ft_mandelbrot(t_vars *vars);
void	ft_julia(t_vars *vars);
int		ft_mlx_key_hook(int keycode, t_vars *vars);
void	init_img(t_vars *vars);
void	ft_fractal(void(*f)(t_vars*), t_vars *vars);
int		ft_color_hsv(double h, double s, double v);
int   	ft_color_argb(t_argb argb);
void	ft_color(int iter, double x, double y, t_vars *vars);
void	ft_menu(t_vars *vars);

#endif
