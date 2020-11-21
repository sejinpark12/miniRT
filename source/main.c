#include "mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>

#define	UP		125
#define	DOWN	126
#define	LEFT	123
#define	RIGHT	124
#define ESC		53

typedef struct 	s_data
{
	void		*mlx;
	void		*mlx_win;
	int			width;
	int			height;
	int			x;
	int			y;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int				ft_move(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		exit(0);
	}
	else if (keycode == LEFT)
	{
		data->x -= 1;
		printf("key = %d, x = %d, y = %d\n", keycode, data->x, data->y);
	}
	else if (keycode == RIGHT)
	{
		data->x += 1;
		printf("key = %d, x = %d, y = %d\n", keycode, data->x, data->y);
	}
	else if (keycode == UP)
	{
		data->y += 1;
		printf("key = %d, x = %d, y = %d\n", keycode, data->x, data->y);
	}
	else if (keycode == DOWN)
	{
		data->y -= 1;
		printf("key = %d, x = %d, y = %d\n", keycode, data->x, data->y);
	}
	return (0);
}

int				ft_draw(t_data *data)
{
	int i;
	int j;
	int k;
	int x = data->x;
	int y = data->y;

	mlx_hook(data->mlx_win, 2, 1L<<0, ft_move, data);
	for (i = 0; i < data->width; i++)
	{
		for (j = 0; j < data->height; j++)
			my_mlx_pixel_put(data, i, j, 0x00000000);
	}
	for (i = x, k = 99; i < x + 50; i++, k -= 2)
	{
		for (j = y + k; j < y + 100; j++)
			my_mlx_pixel_put(data, i, j, 0x0000FF00);
	}
	for (i = x + 50, k = 0; i < x + 100; i++, k += 2)
	{
		for (j = y + k; j < y + 100; j++)
			my_mlx_pixel_put(data, i, j, 0x0000FF00);
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx = mlx_init();
	data.width = 600;
	data.height = 400;
	data.mlx_win = mlx_new_window(data.mlx, data.width, data.height, "miniRT");
	data.img = mlx_new_image(data.mlx, 600, 400);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	data.x = 250;
	data.y = 150;
	//mlx_hook(data.mlx_win, 2, 1L<<0, ft_move, &data);
	mlx_loop_hook(data.mlx, ft_draw, &data);
	mlx_loop(data.mlx);
	return (0);
}
