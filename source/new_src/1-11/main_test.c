/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:50:12 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/02 21:51:26 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "vec.h"
#include "ray.h"
#include "hittable_list.h"
#include "sphere.h"
// 21.02.08 plane.h 추가
#include "plane.h"
#include "square.h"
#include "cylinder.h"
#include "triangle.h"
#include "light.h"
#include "random.h"
#include "camera.h"
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

// 21.02.08 sp, pl 리스트를 한번에 처리하기 까다로워서 일단 분리
//typedef struct	s_obj_lst
//{
//	t_obj		*sp_world;
//	t_obj		*pl_world;
//}				t_obj_lst;
//////////////////////////////////////////////////////////////

typedef	struct	s_engine
{
	t_data		data;
	t_camera	cam;
// 21.02.08 sp, pl 리스트를 한번에 처리하기 까다로워서 일단 분리
	t_obj_lst	*obj_lst;
//////////////////////////////////////////////////////////////
	t_obj_lst	*light_lst;
//	t_dilight	*dili;
//	t_splight	*spli;
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
	x_axis = ft_vec_set_xyz(0.3, 0, 0);
	y_axis = ft_vec_set_xyz(0, 0.3, 0);
	z_axis = ft_vec_set_xyz(0, 0, 0.3);
	
	pos_fb.x = ft_vec_dot(x_axis, cam->w);
	pos_fb.y = ft_vec_dot(y_axis, cam->w);
	pos_fb.z = ft_vec_dot(z_axis, cam->w);
	pos_rl.x = ft_vec_dot(x_axis, cam->u);
	pos_rl.y = ft_vec_dot(y_axis, cam->u);
	pos_rl.z = ft_vec_dot(z_axis, cam->u);
	pos_ud.x = ft_vec_dot(x_axis, cam->v);
	pos_ud.y = ft_vec_dot(y_axis, cam->v);
	pos_ud.z = ft_vec_dot(z_axis, cam->v);

	if (data->left == 1)
	{
		cam->origin.x -= pos_rl.x;
		cam->origin.y -= pos_rl.y;
		cam->origin.z -= pos_rl.z;
	}
	if (data->right == 1)
	{
		cam->origin.x += pos_rl.x;
		cam->origin.y += pos_rl.y;
		cam->origin.z += pos_rl.z;
	}
	if (data->up == 1)
	{
		cam->origin.x += pos_ud.x;
		cam->origin.y += pos_ud.y;
		cam->origin.z += pos_ud.z;
	}
	if (data->down == 1)
	{
		cam->origin.x -= pos_ud.x;
		cam->origin.y -= pos_ud.y;
		cam->origin.z -= pos_ud.z;
	}
	if (data->forward == 1)
	{
		cam->origin.x -= pos_fb.x;
		cam->origin.y -= pos_fb.y;
		cam->origin.z -= pos_fb.z;
	}
	if (data->backward == 1)
	{
		cam->origin.x += pos_fb.x;
		cam->origin.y += pos_fb.y;
		cam->origin.z += pos_fb.z;
	}
// 21.01.30 코드 추가
	if (data->r_rotate == 1 && cam->cam_phi < -1)
	{
		cam->cam_phi += 1;
		cam->dir.x = sin(ft_degrees_to_radians(cam->cam_theta)) * cos(ft_degrees_to_radians(cam->cam_phi));
		cam->dir.y = cos(ft_degrees_to_radians(cam->cam_theta));
		cam->dir.z = sin(ft_degrees_to_radians(cam->cam_theta)) * sin(ft_degrees_to_radians(cam->cam_phi));
	}
	if (data->l_rotate == 1 && cam->cam_phi > -179)
	{
		cam->cam_phi -= 1;
		cam->dir.x = sin(ft_degrees_to_radians(cam->cam_theta)) * cos(ft_degrees_to_radians(cam->cam_phi));
		cam->dir.y = cos(ft_degrees_to_radians(cam->cam_theta));
		cam->dir.z = sin(ft_degrees_to_radians(cam->cam_theta)) * sin(ft_degrees_to_radians(cam->cam_phi));
	}
	if (data->up_rotate == 1 && cam->cam_theta > 1)
	{
		cam->cam_theta -= 1;
		cam->dir.x = sin(ft_degrees_to_radians(cam->cam_theta)) * cos(ft_degrees_to_radians(cam->cam_phi));
		cam->dir.y = cos(ft_degrees_to_radians(cam->cam_theta));
		cam->dir.z = sin(ft_degrees_to_radians(cam->cam_theta)) * sin(ft_degrees_to_radians(cam->cam_phi));
	}
	if (data->down_rotate == 1 && cam->cam_theta < 179)
	{
		cam->cam_theta += 1;
		cam->dir.x = sin(ft_degrees_to_radians(cam->cam_theta)) * cos(ft_degrees_to_radians(cam->cam_phi));
		cam->dir.y = cos(ft_degrees_to_radians(cam->cam_theta));
		cam->dir.z = sin(ft_degrees_to_radians(cam->cam_theta)) * sin(ft_degrees_to_radians(cam->cam_phi));
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

//t_color			ft_ray_color(t_ray *r, t_obj_lst *obj_lst, t_dilight *dili)
//t_color			ft_ray_color(t_ray *r, t_obj_lst *obj_lst, t_splight *spli)
//t_color			ft_ray_color(t_ray *r, t_obj_lst *obj_lst, t_light_lst *light_lst)
t_color			ft_ray_color(t_ray *r, t_obj_lst *obj_lst, t_obj_lst *light_lst)
{
	t_color		color;
	float		t;
	t_hit_rec	rec;
	t_ray		sha_ray;
	t_t			t_minmax;
	t_spli_info spli_info;
	float		tmpcolor;
	int			vis;
	t_obj_lst	*cur_splight_lst;

	t_minmax.min = 0;
	t_minmax.max = FLT_MAX;
	if (ft_hit_lst_obj_hit(obj_lst, r, &t_minmax, &rec))
	{
// 첫번째 버전
//		color = ft_vec3_mul_f(
//					0.5, ft_vec3_add(rec.normal, ft_vec3_set_xyz(1, 1, 1)));
// 두번째 버전
//		tmpcolor = ft_vec3_dot(rec.normal, ft_vec3_mul_f(-1, r->dir));
//		if (tmpcolor < 0)
//			tmpcolor = 0;
//		color = ft_vec3_set_xyz(tmpcolor, tmpcolor, tmpcolor);
// 세번째 버전 - 방향성 조명
//		sha_ray = ft_ray_set(ft_vec3_add(rec.p, ft_vec3_mul_f(1e-4, rec.normal)),
//													ft_vec3_mul_f(-1, dili->dir));
//		vis = (0 == ft_sha_hit_lst_hit(obj_lst, &sha_ray, t_minmax, &shadowrec)) 
//			? 1 : 0;
//		tmpcolor = ft_vec3_dot(rec.normal, ft_vec3_mul_f(-1, dili->dir));
//		color.x = vis * rec.color.x * 0.18 / M_PI * dili->intensity * dili->color.x * tmpcolor;
//		color.y = vis * rec.color.y * 0.18 / M_PI * dili->intensity * dili->color.y * tmpcolor;
//		color.z = vis * rec.color.z * 0.18 / M_PI * dili->intensity * dili->color.z * tmpcolor;
//		printf("color x = %f, y = %f, z = %f \n", rec.color.x, rec.color.y, rec.color.z);
//		printf("color x = %f, y = %f, z = %f \n", color.x, color.y, color.z);
//
// 네 번째 버전 - 다중 포인트 조명
		cur_splight_lst = light_lst;
		color = ft_vec_set_xyz(0, 0, 0);
		while(cur_splight_lst)
		{
			spli_info = ft_splight_get_info(cur_splight_lst->content, &rec.p);
			t_minmax.max = spli_info.distance;
			sha_ray = ft_ray_set(ft_vec_add(rec.p,
						ft_vec_mul_f(1e-4, rec.normal)),
						ft_vec_mul_f(-1, spli_info.lightdir));
			vis = (0 == ft_hit_lst_sha_hit(obj_lst, &sha_ray, &t_minmax)) ? 1 : 0;
			tmpcolor = ft_vec_dot(rec.normal,
						ft_vec_mul_f(-1, spli_info.lightdir));
			if (tmpcolor < 0)
				tmpcolor = 0;
			color.x += vis * rec.color.x * 0.18 / M_PI *
							spli_info.lightintensity.x * tmpcolor;
			color.y += vis * rec.color.y * 0.18 / M_PI *
							spli_info.lightintensity.y * tmpcolor;
			color.z += vis * rec.color.z * 0.18 / M_PI *
							spli_info.lightintensity.z * tmpcolor;
			cur_splight_lst = cur_splight_lst->next;
	//		printf("color x = %f, y = %f, z = %f \n", rec.color.x, rec.color.y, rec.color.z);
	//		printf("color x = %f, y = %f, z = %f \n", spli_info.lightintensity.x, spli_info.lightintensity.y, spli_info.lightintensity.z);
		}
		return (color);
	}
	t = 0.5 * (ft_vec_unit_vec(r->dir).y + 1.0);
	color = ft_vec_add(
				ft_vec_mul_f((1.0 - t), ft_vec_set_xyz(1.0, 1.0, 1.0)),
				ft_vec_mul_f(t, ft_vec_set_xyz(0.5, 0.7, 1.0)));
	return (color);
}

// 21.02.08 sp, pl 리스트를 한번에 처리하기 까다로워서 일단 분리
//int				ft_draw(t_data *data, t_camera *cam, t_obj_lst *obj_lst, t_dilight *dili)
//int				ft_draw(t_data *data, t_camera *cam, t_obj_lst *obj_lst, t_splight *spli)
//int				ft_draw(t_data *data, t_camera *cam, t_obj_lst *obj_lst, t_light_lst *light_lst)
int				ft_draw(t_data *data, t_camera *cam, t_obj_lst *obj_lst, t_obj_lst *light_lst)
/////////////////////////////////////////////////////////////////
{
	int		i;
	int		j;
/* *********************************** 수정 ********************************* */
	int		k;
	t_vec3	color;
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
			color = ft_vec_set_xyz(0, 0, 0);
			while (k < data->samples_per_pixel)
			{
				r = ft_camera_get_ray(*cam,
							((float)i + ft_random_float()) / (data->width - 1),
							((float)j + ft_random_float()) / (data->height - 1));
// 21.02.08 sp, pl 리스트를 한번에 처리하기 까다로워서 일단 분리
				//color = ft_vec3_add(color, ft_ray_color(&r, obj_lst, dili));
				//color = ft_vec_add(color, ft_ray_color(&r, obj_lst, light_lst));
				color = ft_vec_add(color, ft_ray_color(&r, obj_lst, light_lst));
/////////////////////////////////////////////////////////////////
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
//	ft_camera_set(&engine->cam, engine->cam.lookfrom, engine->cam.lookat,
//							engine->cam.vup, 90.0, engine->data.aspect_ratio);
//	printf("origin x = %f, y = %f, z = %f\n", engine->cam.origin.x, engine->cam.origin.y, engine->cam.origin.z);
//	printf("dir x = %f, y = %f, z = %f\n", engine->cam.dir.x, engine->cam.dir.y, engine->cam.dir.z);
	ft_camera_set(&engine->cam, engine->cam.origin, engine->cam.dir, 90.0);
// 21.02.08 sp, pl 리스트를 한번에 처리하기 까다로워서 일단 분리
//	ft_draw(&engine->data, &engine->cam, &engine->obj_lst, engine->dili);
//	ft_draw(&engine->data, &engine->cam, &engine->obj_lst, engine->spli);
//	ft_draw(&engine->data, &engine->cam, &engine->obj_lst, &engine->light_lst);
	ft_draw(&engine->data, &engine->cam, engine->obj_lst, engine->light_lst);
/////////////////////////////////////////////////////////////////
	ft_move(&engine->data, &engine->cam);
	return (0);
}

int	main(void)
{
	t_engine	engine;
	t_sphere	*sp;
// 21.02.08 pl 변수 추가
	t_plane		*pl;
	t_square	*sq;
///////////////////////
	t_cylinder	*cy;
	t_triangle	*tr;
	t_splight	*spli;


	// Image
	engine.data.aspect_ratio = 16.0 / 9.0;
	engine.data.width = 1000;
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
	engine.data.samples_per_pixel = 4;
/* ************************************************************************** */
	// World
	// 사용안하는 도형이더라도 NULL로 선언해줘야 한다. 그렇지 않으면 ft_hit_lst_hit함수에서 세그폴트 뜬다.
//	engine.obj_lst.sp_world = NULL;
//	engine.obj_lst.pl_world = NULL;
//	engine.obj_lst.sq_world = NULL;
//	engine.obj_lst.cy_world = NULL;
//	engine.obj_lst.tr_world = NULL;
	engine.obj_lst = NULL;
	// 빛 추가
	engine.light_lst = NULL;
//	방향성 조명
//	engine.dili = (t_dilight*)malloc(sizeof(t_dilight));
//	*(engine.dili) = ft_dilight_set(ft_vec3_set_xyz(0, 0, 0), ft_vec3_set_xyz(1, -1, -1), 10 , ft_vec3_set_xyz(1, 1, 1));
//	구형 조명
//	engine.spli = (t_splight*)malloc(sizeof(t_splight));
//	*(engine.spli) = ft_splight_set(ft_vec3_set_xyz(0, 50, 20),
//											500000, ft_vec3_set_xyz(1, 1, 1));
//	다중 구형 조명
	spli = (t_splight*)malloc(sizeof(t_splight));
	*(spli) = ft_splight_set(ft_vec_set_xyz(-20, 50, -20),
											500000, ft_vec_set_xyz(0.5, 0.5, 1));
	ft_hit_lst_addback(&engine.light_lst, ft_hit_lst_newobj(spli, 10));
	spli = (t_splight*)malloc(sizeof(t_splight));
	*(spli) = ft_splight_set(ft_vec_set_xyz(20, 50, 20),
											500000, ft_vec_set_xyz(1, 0.5, 0.5));
	ft_hit_lst_addback(&engine.light_lst, ft_hit_lst_newobj(spli, 10));
//	spli = (t_splight*)malloc(sizeof(t_splight));
//	*(spli) = ft_splight_set(ft_vec3_set_xyz(0, 5, 0),
//											10000, ft_vec3_set_xyz(1, 1, 1));
//	ft_hit_lst_add(&engine.light_lst.splight_lst, ft_hit_lst_newnode(spli));
// 도형 ///////////////////////////////////////////
	sp = (t_sphere*)malloc(sizeof(t_sphere));
	*sp = ft_sphere_set(ft_vec_set_xyz(0, 1, -5), 8, ft_vec_set_xyz(1, 0, 0));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(sp, 1));
	sp = (t_sphere*)malloc(sizeof(t_sphere));
	*sp = ft_sphere_set(ft_vec_set_xyz(12, 25, 13), 10, ft_vec_set_xyz(0, 1, 0));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(sp, 1));
	sp = (t_sphere*)malloc(sizeof(t_sphere));
	*sp = ft_sphere_set(ft_vec_set_xyz(-10, 1, -1), 4, ft_vec_set_xyz(0, 0, 1));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(sp, 1));
	sp = (t_sphere*)malloc(sizeof(t_sphere));
	*sp = ft_sphere_set(ft_vec_set_xyz(0, 20, -50), 15, ft_vec_set_xyz(1, 0, 1));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(sp, 1));
 // 21.02.08 pl 생성 코드 추가
	pl = (t_plane*)malloc(sizeof(t_plane));
	*pl = ft_plane_set(ft_vec_set_xyz(0, -3, 0),
						ft_vec_set_xyz(0, 1, 0),
						ft_vec_set_xyz(0.8, 0.8, 0.8));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(pl, 2));
	pl = (t_plane*)malloc(sizeof(t_plane));
	*pl = ft_plane_set(ft_vec_set_xyz(0, 0, -100),
						ft_vec_set_xyz(0, 0, 1),
						ft_vec_set_xyz(0, 1, 1));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(pl, 2));
	pl = (t_plane*)malloc(sizeof(t_plane));
	*pl = ft_plane_set(ft_vec_set_xyz(-100, 0, 0),
						ft_vec_set_xyz(1, 0, 0),
						ft_vec_set_xyz(1, 0, 0));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(pl, 2));
	pl = (t_plane*)malloc(sizeof(t_plane));
	*pl = ft_plane_set(ft_vec_set_xyz(100, 0, 0),
						ft_vec_set_xyz(-1, 0, 0),
						ft_vec_set_xyz(0, 0, 1));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(pl, 2));
	pl = (t_plane*)malloc(sizeof(t_plane));
	*pl = ft_plane_set(ft_vec_set_xyz(0, 100, 0),
						ft_vec_set_xyz(0, -1, 0),
						ft_vec_set_xyz(1, 0, 1));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(pl, 2));
	pl = (t_plane*)malloc(sizeof(t_plane));
	*pl = ft_plane_set(ft_vec_set_xyz(0, 0, 100),
						ft_vec_set_xyz(0, 0, -1),
						ft_vec_set_xyz(1, 1, 0));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(pl, 2));
	sq = (t_square*)malloc(sizeof(t_square));
	*sq = ft_square_set(ft_vec_set_xyz(0, 15, 20),
						ft_vec_set_xyz(0, 1, 0), 5,
						ft_vec_set_xyz(0, 1, 0));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(sq, 3));
	sq = (t_square*)malloc(sizeof(t_square));
	*sq = ft_square_set(ft_vec_set_xyz(-15, 10, 1),
						ft_vec_set_xyz(-1, -1, 1), 10,
						ft_vec_set_xyz(0.3, 0.5, 1));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(sq, 3));
	cy = (t_cylinder*)malloc(sizeof(t_cylinder));
	*cy = ft_cylinder_set(ft_vec_set_xyz(0, 10, -1),
							ft_vec_set_xyz(1, 0, 0),
							3, 10, ft_vec_set_xyz(0, 0, 1));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(cy, 4));
	cy = (t_cylinder*)malloc(sizeof(t_cylinder));
	*cy = ft_cylinder_set(ft_vec_set_xyz(15, 10, 10),
							ft_vec_set_xyz(0, 0, 1),
							10, 15, ft_vec_set_xyz(1, 0.8, 0.5));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(cy, 4));
	tr = (t_triangle*)malloc(sizeof(t_triangle));
	*tr = ft_triangle_set(ft_vec_set_xyz(-10, 0, 20),
							ft_vec_set_xyz(10, 0, 20),
							ft_vec_set_xyz(0, 10, 10), ft_vec_set_xyz(0.5, 0.5, 1));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(tr, 5));
	tr = (t_triangle*)malloc(sizeof(t_triangle));
	*tr = ft_triangle_set(ft_vec_set_xyz(-10, -10, 10),
							ft_vec_set_xyz(10, -10, 0),
							ft_vec_set_xyz(0, 0, 0), ft_vec_set_xyz(1, 0, 0));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(tr, 5));
	tr = (t_triangle*)malloc(sizeof(t_triangle));
	*tr = ft_triangle_set(ft_vec_set_xyz(20, 40, 0),
							ft_vec_set_xyz(15, 4, -40),
							ft_vec_set_xyz(0, 10, -70), ft_vec_set_xyz(0, 1, 0.3));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(tr, 5));
///////////////////////////////////////////////
	// Camera
	engine.cam.origin = ft_vec_set_xyz(-20, 20, 20);
	engine.cam.dir = ft_vec_set_xyz(20, -10, -20);
// 21.01.30 코드 추가
	engine.cam.cam_theta = 90;
	engine.cam.cam_phi = -90;
////////////////////////////////////	
//	ft_camera_set(&engine.cam, engine.cam.lookfrom, engine.cam.lookat,
//								engine.cam.vup, 90.0, engine.data.aspect_ratio);
	ft_camera_set(&engine.cam, ft_vec_set_xyz(-20, 20, 20), ft_vec_set_xyz(20, -10, -20), 90.0);

	// Render
	engine.data.mlx = mlx_init();
	engine.data.mlx_win = mlx_new_window(
										engine.data.mlx, engine.data.width,
										engine.data.height, "miniRT");
	engine.data.img = mlx_new_image(
						engine.data.mlx, engine.data.width, engine.data.height);
	engine.data.addr = mlx_get_data_addr(
								engine.data.img, &engine.data.bits_per_pixel,
								&engine.data.line_length, &engine.data.endian);

	mlx_hook(engine.data.mlx_win, 2, 1L<<0, ft_key_press, &engine.data);
	mlx_hook(engine.data.mlx_win, 3, 1L<<0, ft_key_release, &engine.data);
/************ 실시간 *************/
	//mlx_loop_hook(engine.data.mlx, main_loop, &engine);
/************ 한 프레임 *************/
	//ft_draw(&engine.data, &engine.cam, &engine.obj_lst, engine.dili);
	//ft_draw(&engine.data, &engine.cam, &engine.obj_lst, engine.spli);
	//ft_draw(&engine.data, &engine.cam, &engine.obj_lst, &engine.light_lst);
	ft_draw(&engine.data, &engine.cam, engine.obj_lst, engine.light_lst);
	mlx_loop(engine.data.mlx);
	return (0);
}
