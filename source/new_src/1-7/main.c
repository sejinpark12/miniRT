/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:50:12 by sejpark           #+#    #+#             */
/*   Updated: 2020/12/06 00:05:20 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "vec3.h"
#include "ray.h"
#include "hittable_list.h"
#include "sphere.h"
#include "ft_random.h"
#include "ft_camera.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define ESC			53
#define KeyPress	2
#define KeyRelease	3
#define	PI			3.1415926535897932385

typedef struct 	s_data
{
	void		*mlx;
	void		*mlx_win;
	float		aspect_ratio;
	int			width, height;
/* *********************************** 추가 ********************************* */
	int			samples_per_pixel;
/* ************************************************************************** */
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

float			degrees_to_radians(float degrees)
{
	return (degrees * PI / 180.0);
}

/* *********************************** 수정 ********************************* */
void            my_mlx_pixel_put(t_data *data, int x, int y, t_vec3 *color,
																	int samples_per_pixel)
{
    char    *dst;
	float	r;
	float	g;
	float	b;
	float	scale;

	scale = 1.0 / samples_per_pixel;
	r = color->x * scale;
	g = color->y * scale;
	b = color->z * scale;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = create_trgb(0,
									256 * ft_clamp(r, 0.0, 0.999),
									256 * ft_clamp(g, 0.0, 0.999),
									256 * ft_clamp(b, 0.0, 0.999));
}
/* ************************************************************************** */

int				ft_key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		exit(0);
	}
	return (0);
}

t_color			*ft_ray_color(t_color *target, t_ray *r, t_obj **obj_lst)
{
	t_vec3		unit_dir;
	float		t;
	t_color		cal1;
	t_color		cal2;
	t_hit_rec	rec;
	t_t			t_minmax;

	t_minmax.min = 0;
	t_minmax.max = FLT_MAX;
	if (ft_hit_lst_hit(obj_lst, r, t_minmax, &rec))
	{
		ft_vec3_set_xyz(target, 1, 1, 1);
		ft_vec3_add(target, target, &rec.normal);
		return (ft_vec3_multi_float(target, 0.5, target));
	}
	ft_vec3_unit_vec(&unit_dir, &(r->dir));
	t = 0.5 * (unit_dir.y + 1.0);
	ft_vec3_multi_float(&cal1, (1.0 - t),
									ft_vec3_set_xyz(&cal1, 1.0, 1.0, 1.0));
	ft_vec3_multi_float(&cal2, t, ft_vec3_set_xyz(&cal2, 0.5, 0.7, 1.0));
	return (ft_vec3_add(target, &cal1, &cal2));
}

int				ft_draw(t_data *data, t_camera *cam, t_obj *world)
{
	int		i;
	int		j;
/* *********************************** 수정 ********************************* */
	int		k;
	t_vec3	color;
	t_vec3	tmp_color;
/* ************************************************************************** */
	t_ray	r;

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
			k = 0;
			ft_vec3_set_xyz(&color, 0, 0, 0);
			while (k < data->samples_per_pixel)
			{
				ft_camera_get_ray(&r, cam,
									((float)i + ft_random_float()) / (data->width - 1),
									((float)j + ft_random_float()) / (data->height - 1));
				ft_ray_color(&tmp_color, &r, &world);
				ft_vec3_add(&color, &color, &tmp_color);
				k++;
			}
			my_mlx_pixel_put(data, i, data->height - 1 - j, &color, data->samples_per_pixel);
/* ************************************************************************** */
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
	t_camera	cam;
	t_obj		*world;
	t_point3	center;
	t_sphere	*sp;

	// Image
	data.aspect_ratio = 16.0 / 9.0;
	data.width = 600;
	data.height = (int)(data.width / data.aspect_ratio);
/* *********************************** 추가 ********************************* */
	data.samples_per_pixel = 1;
/* ************************************************************************** */
	// World
	world = NULL;
	sp = (t_sphere*)malloc(sizeof(t_sphere));
	ft_vec3_set_xyz(&center, 0, 0, -1);
	ft_sphere_set(sp, &center, 0.5);
	ft_hit_lst_add(&world, ft_hit_lst_newnode(sp));
	sp = (t_sphere*)malloc(sizeof(t_sphere));
	ft_vec3_set_xyz(&center, 0, -100.5, -1);
	ft_sphere_set(sp, &center, 100);
	ft_hit_lst_add(&world, ft_hit_lst_newnode(sp));
	// Camera
	ft_camera_set(&cam);

	// Render
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, data.width, data.height, "miniRT");
	data.img = mlx_new_image(data.mlx, data.width, data.height);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	mlx_hook(data.mlx_win, 2, 1L<<0, ft_key_press, &data);
	ft_draw(&data, &cam, world);
	mlx_loop(data.mlx);
	return (0);
}
