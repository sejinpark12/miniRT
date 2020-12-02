/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:50:12 by sejpark           #+#    #+#             */
/*   Updated: 2020/12/02 18:23:30 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* *********************************** 수정 ********************************* */
/* ************************************************************************** */
#include "mlx.h"
#include "libft.h"
#include "vec3.h"
#include "ray.h"
#include "hittable_list.h"
#include "sphere.h"
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
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

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

float			degrees_to_radians(float degrees)
{
	return (degrees * PI / 180.0);
}

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

float			ft_hit_sphere(t_point3 *center, float radius, t_ray *r)
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;

	ft_vec3_sub(&oc, &(r->orig), center);
	a = ft_vec3_dot(&(r->dir), &(r->dir));
	b = 2.0 * ft_vec3_dot(&oc, &(r->dir));
	c = ft_vec3_dot(&oc, &oc) - radius * radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1.0);
	else
		return ((-b - sqrt(discriminant)) / (2.0 * a));
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

int				ft_draw(t_data *data, t_camera *cam, t_obj *world)
{
	int		i;
	int		j;
	t_vec3	color;
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
			ft_camera_cal_ray(&r, cam,
								(float)i / (data->width - 1),
								(float)j / (data->height - 1));
			ft_ray_color(&color, &r, &world);
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
	t_camera	cam;
	t_obj		*world;
	t_point3	center;
	t_sphere	*sp;

	data.aspect_ratio = 16.0 / 9.0;
	data.width = 600;
	data.height = (int)(data.width / data.aspect_ratio);
	ft_camera_set(&cam, data.aspect_ratio);
	world = NULL;
	sp = (t_sphere*)malloc(sizeof(t_sphere));
	ft_vec3_set_xyz(&center, 0, 0, -1);
	ft_sphere_set(sp, &center, 0.5);
	ft_hit_lst_add(&world, ft_hit_lst_newnode(sp));
	sp = (t_sphere*)malloc(sizeof(t_sphere));
	ft_vec3_set_xyz(&center, 0, -100.5, -1);
	ft_sphere_set(sp, &center, 100);
	ft_hit_lst_add(&world, ft_hit_lst_newnode(sp));

	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, data.width, data.height, "miniRT");
	data.img = mlx_new_image(data.mlx, data.width, data.height);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	mlx_hook(data.mlx_win, 2, 1L<<0, ft_key_press, &data);
	ft_draw(&data, &cam, world);
	mlx_loop(data.mlx);
	return (0);
}
