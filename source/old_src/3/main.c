/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:09:31 by sejpark           #+#    #+#             */
/*   Updated: 2020/11/20 19:39:54 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx/mlx.h"
#include "miniRT.h"
#include "vec3.h"
#include "ray.h"
#include "hittable_list.h"
#include "sphere.h"
#include <stdio.h>
#include <float.h>

typedef	struct	s_coord
{
	t_vec3		origin;
	t_vec3		horizontal;
	t_vec3		vertical;
	t_vec3		lower_left_corner;
}				t_coord;

typedef	struct	s_camera
{
	int			width;
	int			height;
	float		aspect_ratio;
	float		viewport_height;
	float		viewport_width;
	float		focal_length;
}				t_camera;



void print_vec3(const t_vec3 *v)
{
	printf("e0 = %f, e1 = %f, e2 = %f\n", v->e[0], v->e[1], v->e[2]);
}

t_vec3 *ray_color(const t_ray *r, object **obj_lst)
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

void my_mlx_pixel_put(t_data *data, int x, int y, const t_vec3 *color)
{
	char	*dst;

	dst = data->addr
		  + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = create_trgb(0,
									  ft_vec3_get_x(color) * 255.999,
									  ft_vec3_get_y(color) * 255.999,
									  ft_vec3_get_z(color) * 255.999);
}

void ft_make_image(t_data *data, t_camera cam, t_coord coord, object *obj_lst)
{
	int		i;
	int		j;
	float	u;
	float	v;
	t_vec3	ray_set_cal;
	t_ray	r;
	t_vec3	*pixel_color;

	j = cam.height - 1;
	while (j >= 0)
	{
		i = 0;
		ft_putstr_fd("\rScanlines remaining: ", 1);
		ft_putnbr_fd(j, 1);
		ft_putchar_fd(' ', 1);
		while (i < cam.width)
		{
			u = (float)(i) / (cam.width - 1);
			v = (float)(j) / (cam.height - 1);
			ray_set_cal.e[0] = coord.lower_left_corner.e[0]
								+ u * coord.horizontal.e[0]
								+ v * coord.vertical.e[0]
								- coord.origin.e[0];
			ray_set_cal.e[1] = coord.lower_left_corner.e[1]
								+ u * coord.horizontal.e[1]
								+ v * coord.vertical.e[1]
								- coord.origin.e[1];
			ray_set_cal.e[2] = coord.lower_left_corner.e[2]
								+ u * coord.horizontal.e[2]
								+ v * coord.vertical.e[2]
								- coord.origin.e[2];
			ft_ray_set(&r, &coord.origin, &ray_set_cal);
			pixel_color = ray_color(&r, &obj_lst);
			my_mlx_pixel_put(data, i, (cam.height - 1) - j, pixel_color);
			free(r.orig);
			free(r.dir);
			free(pixel_color);
			i++;
		}
		j--;
	}
	ft_putstr_fd("\nComplete!", 1);
}

void	ft_init_camera(t_camera * camera)
{
	camera->aspect_ratio = 16.0 / 9.0;
	camera->width = 1920;
	camera->height = camera->width / camera->aspect_ratio;

	// 카메라
	camera->viewport_height = 2.0;
	camera->viewport_width = camera->aspect_ratio * camera->viewport_height;
	camera->focal_length = 1.0;
}

void	ft_init_coord(t_coord *coord, t_camera *camera)
{
	t_vec3	*origin;
	t_vec3	*horizontal;
	t_vec3	*vertical;
	t_vec3	*lower_left_corner;

	origin = &(coord->origin);
	horizontal = &(coord->horizontal);
	vertical = &(coord->vertical);
	lower_left_corner = &(coord->lower_left_corner);
	ft_vec3_set_rgb(origin, 0, 0, 0);
	ft_vec3_set_rgb(horizontal, camera->viewport_width, 0, 0);
	ft_vec3_set_rgb(vertical, 0, camera->viewport_height, 0);
	lower_left_corner->e[0] = origin->e[0]
								- (horizontal->e[0] / 2)
								- (vertical->e[0] / 2) - 0; 
	lower_left_corner->e[1] = origin->e[1]
								- (horizontal->e[1] / 2)
								- (vertical->e[1] / 2) - 0; 
	lower_left_corner->e[2] = origin->e[2]
								- (horizontal->e[2] / 2)
								- (vertical->e[2] / 2) - camera->focal_length; 
}

int main(void)
{
	void		*mlx;
	void		*mlx_win;
	t_data		img;
	t_coord		coord;
	t_camera	camera;
	object		*obj_lst;
	point3		center;
	t_sphere	*newnode;

	ft_init_camera(&camera);
	ft_init_coord(&coord, &camera);

	obj_lst = NULL;
	newnode = (t_sphere*)malloc(sizeof(t_sphere));
	ft_vec3_set_rgb(&center, 0, 0, -1);
	ft_sphere_set(newnode, &center, 0.5);
	hit_lst_add(&obj_lst, hit_lst_newnode(newnode));
	newnode = (t_sphere*)malloc(sizeof(t_sphere));
	ft_vec3_set_rgb(&center, 0, -100.5, -1);
	ft_sphere_set(newnode, &center, 100);
	hit_lst_add(&obj_lst, hit_lst_newnode(newnode));

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, camera.width, camera.height, "Hello world!");
	img.img = mlx_new_image(mlx, camera.width, camera.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
									&img.endian);
	ft_make_image(&img, camera, coord, obj_lst);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
