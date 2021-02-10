/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:50:12 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/01 00:12:34 by sejpark          ###   ########.fr       */
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

#define UP          126
#define DOWN        125
#define LEFT        123
#define RIGHT       124
#define W           13
#define S           1
#define A           0
#define D           2
// 21.01.31 코드 추가
#define R           15
#define F           3
/////////////////////////////////////////////////////////////
#define ESC			53
#define KeyPress	2
#define KeyRelease	3

typedef struct 	s_data
{
	void		*mlx;
	void		*mlx_win;
	float		aspect_ratio;
	int			width, height;
	int			x, y, z;
// 21.01.30  r_rotate, l_rotate 변수 추가 
	int			up, down, left, right, forward, backward, r_rotate, l_rotate, up_rotate, down_rotate; 
/////////////////////////////////////////////////////////////
/* *********************************** 추가 ********************************* */
	int			samples_per_pixel;
/* ************************************************************************** */
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef	struct	s_engine
{
	t_data		data;
	t_camera	cam;
	t_obj		*world;
}				t_engine;

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

int				ft_move(t_data *data, t_camera *cam)
{
	t_vec3 x_axis;
	t_vec3 y_axis;
	t_vec3 z_axis;

	t_vec3 pos_fb;
	t_vec3 pos_rl;
	t_vec3 pos_ud;

	// 원래 단위 벡터로 설정했는데 이동 속도가 너무 빨라서 일단 벡터 크기를 줄임
	ft_vec3_set_xyz(&x_axis, 0.3, 0, 0);
	ft_vec3_set_xyz(&y_axis, 0, 0.3, 0);
	ft_vec3_set_xyz(&z_axis, 0, 0, 0.3);
	
	pos_fb.x = ft_vec3_dot(&x_axis, &cam->w);
	pos_fb.y = ft_vec3_dot(&y_axis, &cam->w);
	pos_fb.z = ft_vec3_dot(&z_axis, &cam->w);
	pos_rl.x = ft_vec3_dot(&x_axis, &cam->u);
	pos_rl.y = ft_vec3_dot(&y_axis, &cam->u);
	pos_rl.z = ft_vec3_dot(&z_axis, &cam->u);
	pos_ud.x = ft_vec3_dot(&x_axis, &cam->v);
	pos_ud.y = ft_vec3_dot(&y_axis, &cam->v);
	pos_ud.z = ft_vec3_dot(&z_axis, &cam->v);

	if (data->left == 1)
	{
		cam->lookfrom.x -= pos_rl.x;
		cam->lookfrom.y -= pos_rl.y;
		cam->lookfrom.z -= pos_rl.z;
		cam->lookat.x -= pos_rl.x;
		cam->lookat.y -= pos_rl.y;
		cam->lookat.z -= pos_rl.z;
//		cam->lookfrom.x -= 0.1;
//		cam->lookat.x -= 0.1;
	}
	if (data->right == 1)
	{
		cam->lookfrom.x += pos_rl.x;
		cam->lookfrom.y += pos_rl.y;
		cam->lookfrom.z += pos_rl.z;
		cam->lookat.x += pos_rl.x;
		cam->lookat.y += pos_rl.y;
		cam->lookat.z += pos_rl.z;
//		cam->lookfrom.x += 0.1;
//		cam->lookat.x += 0.1;
	}
	if (data->up == 1)
	{
		cam->lookfrom.x += pos_ud.x;
		cam->lookfrom.y += pos_ud.y;
		cam->lookfrom.z += pos_ud.z;
		cam->lookat.x += pos_ud.x;
		cam->lookat.y += pos_ud.y;
		cam->lookat.z += pos_ud.z;
//		cam->lookfrom.y += 0.1;
//		cam->lookat.y += 0.1;
	}
	if (data->down == 1)
	{
		cam->lookfrom.x -= pos_ud.x;
		cam->lookfrom.y -= pos_ud.y;
		cam->lookfrom.z -= pos_ud.z;
		cam->lookat.x -= pos_ud.x;
		cam->lookat.y -= pos_ud.y;
		cam->lookat.z -= pos_ud.z;
//		cam->lookfrom.y -= 0.1;
//		cam->lookat.y -= 0.1;
	}
	if (data->forward == 1)
	{
		cam->lookfrom.x -= pos_fb.x;
		cam->lookfrom.y -= pos_fb.y;
		cam->lookfrom.z -= pos_fb.z;
		cam->lookat.x -= pos_fb.x;
		cam->lookat.y -= pos_fb.y;
		cam->lookat.z -= pos_fb.z;
//		cam->lookfrom.z -= 0.1;
//		cam->lookat.z -= 0.1;
	}
	if (data->backward == 1)
	{
		cam->lookfrom.x += pos_fb.x;
		cam->lookfrom.y += pos_fb.y;
		cam->lookfrom.z += pos_fb.z;
		cam->lookat.x += pos_fb.x;
		cam->lookat.y += pos_fb.y;
		cam->lookat.z += pos_fb.z;
//		cam->lookfrom.z += 0.1;
//		cam->lookat.z += 0.1;
	}
// 21.01.30 코드 추가
	if (data->r_rotate == 1 && cam->cam_phi < -1)
	{
		cam->cam_phi += 1;
		cam->lookat.x = cam->lookfrom.x + sin(ft_degrees_to_radians(cam->cam_theta)) * cos(ft_degrees_to_radians(cam->cam_phi));
		cam->lookat.y = cam->lookfrom.y + cos(ft_degrees_to_radians(cam->cam_theta));
		cam->lookat.z = cam->lookfrom.z + sin(ft_degrees_to_radians(cam->cam_theta)) * sin(ft_degrees_to_radians(cam->cam_phi));
	}
	if (data->l_rotate == 1 && cam->cam_phi > -179)
	{
		cam->cam_phi -= 1;
		cam->lookat.x = cam->lookfrom.x + sin(ft_degrees_to_radians(cam->cam_theta)) * cos(ft_degrees_to_radians(cam->cam_phi));
		cam->lookat.y = cam->lookfrom.y + cos(ft_degrees_to_radians(cam->cam_theta));
		cam->lookat.z = cam->lookfrom.z + sin(ft_degrees_to_radians(cam->cam_theta)) * sin(ft_degrees_to_radians(cam->cam_phi));
	}
	if (data->up_rotate == 1 && cam->cam_theta > 1)
	{
		cam->cam_theta -= 1;
		cam->lookat.x = cam->lookfrom.x + sin(ft_degrees_to_radians(cam->cam_theta)) * cos(ft_degrees_to_radians(cam->cam_phi));
		cam->lookat.y = cam->lookfrom.y + cos(ft_degrees_to_radians(cam->cam_theta));
		cam->lookat.z = cam->lookfrom.z + sin(ft_degrees_to_radians(cam->cam_theta)) * sin(ft_degrees_to_radians(cam->cam_phi));
	}
	if (data->down_rotate == 1 && cam->cam_theta < 179)
	{
		cam->cam_theta += 1;
		cam->lookat.x = cam->lookfrom.x + sin(ft_degrees_to_radians(cam->cam_theta)) * cos(ft_degrees_to_radians(cam->cam_phi));
		cam->lookat.y = cam->lookfrom.y + cos(ft_degrees_to_radians(cam->cam_theta));
		cam->lookat.z = cam->lookfrom.z + sin(ft_degrees_to_radians(cam->cam_theta)) * sin(ft_degrees_to_radians(cam->cam_phi));
	}
	if (cam->cam_phi < -360)
	{
		cam->cam_phi = 0;
	}
	if (cam->cam_phi > 360)
	{
		cam->cam_phi = 0;
	}
	if (cam->cam_theta < -360)
	{
		cam->cam_theta = 0;
	}
	if (cam->cam_theta > 360)
	{
		cam->cam_theta = 0;
	}
	printf("lookfrom : x = %f, y= %f z = %f\n", cam->lookfrom.x, cam->lookfrom.y, cam->lookfrom.z);
	printf("lookat : x = %f, y = %f z = %f\n", cam->lookat.x, cam->lookat.y, cam->lookat.z);
	printf("phi = %f, theta %f\n", cam->cam_phi, cam->cam_theta);
//////////////////////////////////////////////
	return (0);
}
int				ft_key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		exit(0);
	}
	if (keycode == LEFT)
		data->left = 1;
	if (keycode == RIGHT)
		data->right = 1;
	if (keycode == UP)
		data->forward = 1;
	if (keycode == DOWN)
		data->backward = 1;
	if (keycode == R)
		data->up = 1;
	if (keycode == F)
		data->down = 1;
// 21.01.30 코드 추가
	if (keycode == W)
		data->up_rotate = 1;
	if (keycode == S)
		data->down_rotate = 1;
//////////////////////////////////////////////
// 21.01.31 코드 추가
	if (keycode == D)
		data->r_rotate = 1;
	if (keycode == A)
		data->l_rotate = 1;
//////////////////////////////////////////////
	return (0);
}

int				ft_key_release(int keycode, t_data *data)
{
	if (keycode == LEFT)
		data->left = 0;
	if (keycode == RIGHT)
		data->right = 0;
	if (keycode == UP)
		data->forward = 0;
	if (keycode == DOWN)
		data->backward = 0;
	if (keycode == R)
		data->up = 0;
	if (keycode == F)
		data->down = 0;
// 21.01.30 코드 추가
	if (keycode == W)
		data->up_rotate = 0;
	if (keycode == S)
		data->down_rotate = 0;
//////////////////////////////////////////////
// 21.01.31 코드 추가
	if (keycode == D)
		data->r_rotate = 0;
	if (keycode == A)
		data->l_rotate = 0;
//////////////////////////////////////////////
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
//	printf("start!\n");
	if (ft_hit_lst_hit(obj_lst, r, t_minmax, &rec))
	{
//		printf("hit!\n");
		ft_vec3_set_xyz(target, 1, 1, 1);
		ft_vec3_add(target, target, &rec.normal);
		return (ft_vec3_multi_float(target, 0.5, target));
	}
//	printf("not hit!\n");
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
//		ft_putstr_fd("\rScanlines remaining: ", 1);
//		ft_putnbr_fd(j, 1);
//		ft_putchar_fd(' ', 1);
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

int main_loop(t_engine *engine)
{
	ft_camera_set(&engine->cam, &engine->cam.lookfrom, &engine->cam.lookat,
										&engine->cam.vup, 90.0, engine->data.aspect_ratio);
	ft_draw(&engine->data, &engine->cam, engine->world);
	ft_move(&engine->data, &engine->cam);
	return (0);
}

int	main(void)
{
	t_engine	engine;
	t_point3	center;
	t_sphere	*sp;

	// Image
	engine.data.aspect_ratio = 16.0 / 9.0;
	engine.data.width = 200;
	engine.data.height = (int)(engine.data.width / engine.data.aspect_ratio);
	engine.data.right = 0;
	engine.data.left = 0;
	engine.data.up = 0;
	engine.data.down = 0;
	engine.data.forward = 0;
	engine.data.backward = 0;
// 21.01.30 코드 추가
	engine.data.r_rotate = 0;
	engine.data.l_rotate = 0;
////////////////////////////////////	
// 21.01.31 코드 추가
	engine.data.up_rotate = 0;
	engine.data.down_rotate = 0;
////////////////////////////////////	
/* *********************************** 추가 ********************************* */
	engine.data.samples_per_pixel = 1;
/* ************************************************************************** */
	// World
	engine.world = NULL;
	sp = (t_sphere*)malloc(sizeof(t_sphere));
	ft_vec3_set_xyz(&center, 0, 0, -1);
	ft_sphere_set(sp, &center, 0.5);
	ft_hit_lst_add(&engine.world, ft_hit_lst_newnode(sp));
	sp = (t_sphere*)malloc(sizeof(t_sphere));
	ft_vec3_set_xyz(&center, 0, -100.5, -1);
	ft_sphere_set(sp, &center, 100);
	ft_hit_lst_add(&engine.world, ft_hit_lst_newnode(sp));
	// Camera
	ft_vec3_set_xyz(&engine.cam.lookfrom, 0, 0, 0);
	ft_vec3_set_xyz(&engine.cam.lookat, 0, 0, -1);
	ft_vec3_set_xyz(&engine.cam.vup, 0, 1, 0);
// 21.01.30 코드 추가
	engine.cam.cam_theta = 90;
	engine.cam.cam_phi = -90;
////////////////////////////////////	
	ft_camera_set(&engine.cam, &engine.cam.lookfrom, &engine.cam.lookat,
										&engine.cam.vup, 90.0, engine.data.aspect_ratio);

	// Render
	engine.data.mlx = mlx_init();
	engine.data.mlx_win = mlx_new_window(engine.data.mlx, engine.data.width,
														engine.data.height, "miniRT");
	engine.data.img = mlx_new_image(engine.data.mlx, engine.data.width, engine.data.height);
	engine.data.addr = mlx_get_data_addr(engine.data.img, &engine.data.bits_per_pixel,
											&engine.data.line_length, &engine.data.endian);

	mlx_hook(engine.data.mlx_win, 2, 1L<<0, ft_key_press, &engine.data);
	mlx_hook(engine.data.mlx_win, 3, 1L<<0, ft_key_release, &engine.data);
	mlx_loop_hook(engine.data.mlx, main_loop, &engine);
	mlx_loop(engine.data.mlx);
	return (0);
}
