/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:50:12 by sejpark           #+#    #+#             */
/*   Updated: 2020/11/28 18:36:29 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "vec3.h"
#include "ray.h"
#include <stdio.h>
#include <stdlib.h>

#define ESC			53
#define KeyPress	2
#define KeyRelease	3

typedef struct 	s_data
{
	void		*mlx;
	void		*mlx_win;
/* *********************************** 추가 ********************************* */
	float		aspect_ratio;
/* ************************************************************************** */
	int			width, height;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

/* *********************************** 추가 ********************************* */
typedef struct	s_camera
{
	float		viewport_height;
	float		viewport_width;
	float		focal_length;
	t_point3	origin;
	t_vec3		horizontal;
	t_vec3		vertical;
	t_vec3		lower_left_corner;
}				t_camera;
/* ************************************************************************** */

void            my_mlx_pixel_put(t_data *data, int x, int y, t_vec3 *color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = create_trgb(0,
									255.999 * color->x,
									255.999 * color->y,
									255.999 * color->z);
}

int				ft_key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		exit(0);
	}
	return (0);
}

/* *********************************** 추가 ********************************* */
void			ft_camera_set(t_camera *cam, float aspect_ratio)
{
	cam->viewport_height = 2.0;
	cam->viewport_width = aspect_ratio * cam->viewport_height;
	cam->focal_length = 1.0;
	ft_vec3_set_xyz(&cam->origin, 0.0, 0.0, 0.0);
	ft_vec3_set_xyz(&cam->horizontal, cam->viewport_width, 0.0, 0.0);
	ft_vec3_set_xyz(&cam->vertical, 0.0, cam->viewport_height, 0.0);
	cam->lower_left_corner.x = cam->origin.x
								- (cam->horizontal.x / 2)
								- (cam->vertical.x / 2) - 0; 
	cam->lower_left_corner.y = cam->origin.y
								- (cam->horizontal.y / 2)
								- (cam->vertical.y / 2) - 0; 
	cam->lower_left_corner.z = cam->origin.z
								- (cam->horizontal.z / 2)
								- (cam->vertical.z / 2)
								- cam->focal_length; 
}

t_ray			*ft_camera_cal_ray(t_ray *target, t_camera *cam,
															float u, float v)
{
	t_vec3 cal;

	cal.x = cam->lower_left_corner.x
			+ u * cam->horizontal.x
			+ v * cam->vertical.x
			- cam->origin.x;
	cal.y = cam->lower_left_corner.y
			+ u * cam->horizontal.y
			+ v * cam->vertical.y
			- cam->origin.y;
	cal.z = cam->lower_left_corner.z
			+ u * cam->horizontal.z
			+ v * cam->vertical.z
			- cam->origin.z;
	return (ft_ray_set(target, &(cam->origin), &cal));
}

t_color			*ft_ray_color(t_color *target, t_ray *r)
{
	t_vec3	unit_dir;
	float	t;
	t_color	cal1;
	t_color cal2;

	ft_vec3_unit_vec(&unit_dir, &(r->dir));
	printf("unit_y = %f\n", unit_dir.y);
	t = 0.5 * (unit_dir.y + 1.0);
	ft_vec3_multi_float(&cal1, (1.0 - t),
									ft_vec3_set_xyz(&cal1, 1.0, 1.0, 1.0));
	ft_vec3_multi_float(&cal2, t, ft_vec3_set_xyz(&cal2, 0.5, 0.7, 1.0));
	return (ft_vec3_add(target, &cal1, &cal2));
}
/* ************************************************************************** */

int				ft_draw(t_data *data, t_camera *cam)
{
	int		i;
	int		j;
	t_vec3	color;
/* *********************************** 추가 ********************************* */
	t_ray	r;
/* ************************************************************************** */

	j = data->height - 1;
	while (j >= 0)
	{
		i = 0;
		ft_putstr_fd("\rScanlines remaining: ", 1);
		ft_putnbr_fd(j, 1);
		ft_putchar_fd(' ', 1);
		while (i < data->width)
		{
/* *********************************** 수정 ********************************* */
			ft_camera_cal_ray(&r, cam,
								(float)i / (data->width - 1),
								(float)j / (data->height - 1));
			ft_ray_color(&color, &r);
/* ************************************************************************** */
			my_mlx_pixel_put(data, i, data->height - 1 - j, &color);
			i++;
		}
		j--;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	return (0);
}

int	main(void)
{
	t_data		data;
/* *********************************** 추가 ********************************* */
	t_camera	cam;

	data.aspect_ratio = 16.0 / 9.0;
	data.width = 600;
	data.height = (int)(data.width / data.aspect_ratio);
	ft_camera_set(&cam, data.aspect_ratio);
/* ************************************************************************** */
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, data.width, data.height, "miniRT");
	data.img = mlx_new_image(data.mlx, 600, 400);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	mlx_hook(data.mlx_win, 2, 1L<<0, ft_key_press, &data);
/* *********************************** 수정 ********************************* */
	ft_draw(&data, &cam);
/* ************************************************************************** */
	mlx_loop(data.mlx);
	return (0);
}