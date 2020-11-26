/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:09:31 by sejpark           #+#    #+#             */
/*   Updated: 2020/11/25 16:02:54 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx/mlx.h"
#include "minirt.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include <stdio.h>
#include <float.h>

void print_vec3(const t_vec3 *v)
{
	printf("e0 = %f, e1 = %f, e2 = %f\n", v->e[0], v->e[1], v->e[2]);
}

t_vec3 *ray_color(const t_ray *r, t_object **obj_lst)
{
	t_hit_rec rec;
	t_vec3	unit_direction;
	float	t;
	t_vec3	color1;
	t_vec3	color2;
	t_vec3	tmp1;
	t_vec3	tmp2;
//	t_vec3	tmp3;
//	t_vec3	normal; 
	t_vec3	*result;

	result = (t_vec3*)malloc(sizeof(t_vec3));
	if (hit_lst_hit(obj_lst, r, 0, FLT_MAX, &rec))
	{
		ft_vec3_set_rgb(&color1, 1, 1, 1);
		return (ft_vec3_multiply_float(result, 0.5, ft_vec3_add(&color1, &(rec.normal), &color1)));
	}
	ft_unit_vector(&unit_direction, ft_ray_direction(r));
	t = 0.5 * (unit_direction.e[1] + 1.0);
	ft_vec3_set_rgb(&color1, 1.0, 1.0, 1.0);
	ft_vec3_set_rgb(&color2, 0.5, 0.7, 1.0);
	ft_vec3_multiply_float(&tmp1, 1.0 - t, &color1);
	ft_vec3_multiply_float(&tmp2, t, &color2);
	ft_vec3_add(result, &tmp1, &tmp2);
	return (result);

//	result = (t_vec3*)malloc(sizeof(t_vec3));
//	ft_vec3_set_rgb(&color1, 0, 0, -1);
//	t = hit_sphere(&color1, 0.5, r);
//	if (t > 0.0)
//	{
//		ft_vec3_set_rgb(&tmp2, 0, 0, -1);
//		ft_ray_at(&tmp3, r, t);
//		ft_vec3_subtract(&tmp1, &tmp3, &tmp2);
//		ft_unit_vector(&normal, &tmp1);
//		ft_vec3_set_rgb(result, normal.e[0] + 1, normal.e[1] + 1, normal.e[2] + 1);
//		ft_vec3_multiply_float(result, 0.5, result);
//		return (result);
//	}
//	ft_unit_vector(&unit_direction, ft_ray_direction(r));
//	t = 0.5 * (unit_direction.e[1] + 1.0);
//	ft_vec3_set_rgb(&color1, 1.0, 1.0, 1.0);
//	ft_vec3_set_rgb(&color2, 0.5, 0.7, 1.0);
//	ft_vec3_multiply_float(&tmp1, 1.0 - t, &color1);
//	ft_vec3_multiply_float(&tmp2, t, &color2);
//	ft_vec3_add(result, &tmp1, &tmp2);
//	return (result);
}

void my_mlx_pixel_put(t_data *data, int x, int y, const t_vec3 *color, int samples_per_pixel)
{
	float	r;
	float	g;
	float	b;
	float	scale;
	char	*dst;

	r = ft_vec3_get_x(color);
	g = ft_vec3_get_y(color);
	b = ft_vec3_get_z(color);
	scale = 1.0 / samples_per_pixel;
	r *= scale;
	g *= scale;
	b *= scale;
	dst = data->addr
		  + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = create_trgb(0,
									  256 * ft_clamp(r, 0.0, 0.999),
									  256 * ft_clamp(g, 0.0, 0.999),
									  256 * ft_clamp(b, 0.0, 0.999));
}

void ft_make_image(t_data *data, t_camera cam, t_object *obj_lst)
{
	int		i;
	int		j;
	int		s;
	float	u;
	float	v;
	t_ray	r;
	t_vec3	pixel_color;

	j = cam.image_height - 1;
	while (j >= 0)
	{
		i = 0;
		ft_putstr_fd("\rScanlines remaining: ", 1);
		ft_putnbr_fd(j, 1);
		ft_putchar_fd(' ', 1);
		while (i < cam.image_width)
		{
			s = 0;
			ft_vec3_set_rgb(&pixel_color, 0, 0, 0);
			while (s < cam.samples_per_pixel)
			{
				u = (float)(i + random_float()) / (cam.image_width - 1);
				v = (float)(j + random_float()) / (cam.image_height - 1);
				ft_get_ray(&r, &cam, u, v);
				ft_vec3_add(&pixel_color, &pixel_color, ray_color(&r, &obj_lst));
				s++;
			}
			my_mlx_pixel_put(data, i, (cam.image_height - 1) - j, &pixel_color, cam.samples_per_pixel);
			free(r.orig);
			free(r.dir);
			i++;
		}
		j--;
	}
	ft_putstr_fd("\nComplete!", 1);
}



int main(void)
{
	void		*mlx;
	void		*mlx_win;
	t_data		img;
	t_camera	camera;
	t_object	*obj_lst;
	t_point3	center;
	t_sphere	*newnode;

	camera.aspect_ratio = 16.0 / 9.0;
	camera.image_width = 1920;
	camera.image_height = camera.image_width / camera.aspect_ratio;
	camera.samples_per_pixel = 100;

	obj_lst = NULL;
	newnode = (t_sphere*)malloc(sizeof(t_sphere));
	ft_vec3_set_rgb(&center, 0, 0, -1);
	ft_sphere_set(newnode, &center, 0.5);
	hit_lst_add(&obj_lst, hit_lst_newnode(newnode));
	newnode = (t_sphere*)malloc(sizeof(t_sphere));
	ft_vec3_set_rgb(&center, 0, -100.5, -1);
	ft_sphere_set(newnode, &center, 100);
	hit_lst_add(&obj_lst, hit_lst_newnode(newnode));

	ft_camera_set(&camera);
	
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, camera.image_width, camera.image_height, "Hello world!");
	img.img = mlx_new_image(mlx, camera.image_width, camera.image_height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
									&img.endian);
	ft_make_image(&img, camera, obj_lst);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
