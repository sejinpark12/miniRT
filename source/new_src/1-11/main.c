/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:50:12 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/03 22:36:14 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

int	main(void)
{
	t_engine	engine;
	t_imgs		imgs;
	t_cams		cams;
	t_objs		objs;
	t_lights	lights;
	t_obj_lst	*tmp_cam_lst;

	mlx_get_screen_size(engine.data.mlx, &engine.data.width, &engine.data.height);
	printf("x = %d , y = %d\n", engine.data.width, engine.data.height);

	// Image
	engine.data.aspect_ratio = 16.0 / 9.0;
	engine.data.width = 500;
	engine.data.height = (int)(engine.data.width / engine.data.aspect_ratio);
	engine.data.samples_per_pixel = 1;
	// World
	engine.obj_lst = NULL;
	// light
	engine.light_lst = NULL;
	// camera
	engine.cam_lst = NULL;
	engine.head_cam = NULL;
	// image
	engine.data.img_lst = NULL;
	engine.data.current_img_lst = NULL;
	//	다중 구형 조명
	lights.spli = (t_splight*)malloc(sizeof(t_splight));
	*(lights.spli) = ft_splight_set(ft_vec_set_xyz(-20, 50, -20),
											500000, ft_vec_set_xyz(0.5, 0.5, 1));
	ft_hit_lst_addback(&engine.light_lst, ft_hit_lst_newobj(lights.spli, 10));
	lights.spli = (t_splight*)malloc(sizeof(t_splight));
	*(lights.spli) = ft_splight_set(ft_vec_set_xyz(20, 50, 20),
											500000, ft_vec_set_xyz(1, 0.5, 0.5));
	ft_hit_lst_addback(&engine.light_lst, ft_hit_lst_newobj(lights.spli, 10));
	// 도형
	// 구
	objs.sp = (t_sphere*)malloc(sizeof(t_sphere));
	*(objs.sp) = ft_sphere_set(ft_vec_set_xyz(0, 1, -5), 8, ft_vec_set_xyz(1, 0, 0));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(objs.sp, 1));
	objs.sp = (t_sphere*)malloc(sizeof(t_sphere));
	*(objs.sp) = ft_sphere_set(ft_vec_set_xyz(12, 25, 13), 10, ft_vec_set_xyz(0, 1, 0));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(objs.sp, 1));
	objs.sp = (t_sphere*)malloc(sizeof(t_sphere));
	*(objs.sp) = ft_sphere_set(ft_vec_set_xyz(-10, 1, -1), 4, ft_vec_set_xyz(0, 0, 1));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(objs.sp, 1));
	objs.sp = (t_sphere*)malloc(sizeof(t_sphere));
	*(objs.sp) = ft_sphere_set(ft_vec_set_xyz(0, 20, -50), 15, ft_vec_set_xyz(1, 0, 1));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(objs.sp, 1));
	// 평면
	objs.pl = (t_plane*)malloc(sizeof(t_plane));
	*(objs.pl) = ft_plane_set(ft_vec_set_xyz(0, -3, 0),
						ft_vec_set_xyz(0, 1, 0),
						ft_vec_set_xyz(0.8, 0.8, 0.8));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(objs.pl, 2));
	objs.pl = (t_plane*)malloc(sizeof(t_plane));
	*(objs.pl) = ft_plane_set(ft_vec_set_xyz(0, 0, -100),
						ft_vec_set_xyz(0, 0, 1),
						ft_vec_set_xyz(0, 1, 1));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(objs.pl, 2));
	objs.pl = (t_plane*)malloc(sizeof(t_plane));
	*(objs.pl) = ft_plane_set(ft_vec_set_xyz(-100, 0, 0),
						ft_vec_set_xyz(1, 0, 0),
						ft_vec_set_xyz(1, 0, 0));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(objs.pl, 2));
	objs.pl = (t_plane*)malloc(sizeof(t_plane));
	*(objs.pl) = ft_plane_set(ft_vec_set_xyz(100, 0, 0),
						ft_vec_set_xyz(-1, 0, 0),
						ft_vec_set_xyz(0, 0, 1));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(objs.pl, 2));
	objs.pl = (t_plane*)malloc(sizeof(t_plane));
	*(objs.pl) = ft_plane_set(ft_vec_set_xyz(0, 100, 0),
						ft_vec_set_xyz(0, -1, 0),
						ft_vec_set_xyz(1, 0, 1));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(objs.pl, 2));
	objs.pl = (t_plane*)malloc(sizeof(t_plane));
	*(objs.pl) = ft_plane_set(ft_vec_set_xyz(0, 0, 100),
						ft_vec_set_xyz(0, 0, -1),
						ft_vec_set_xyz(1, 1, 0));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(objs.pl, 2));
	// 정사각형
	objs.sq = (t_square*)malloc(sizeof(t_square));
	*(objs.sq) = ft_square_set(ft_vec_set_xyz(0, 15, 20),
						ft_vec_set_xyz(0, 1, 0), 5,
						ft_vec_set_xyz(0, 1, 0));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(objs.sq, 3));
	objs.sq = (t_square*)malloc(sizeof(t_square));
	*(objs.sq) = ft_square_set(ft_vec_set_xyz(-15, 10, 1),
						ft_vec_set_xyz(-1, -1, 1), 10,
						ft_vec_set_xyz(0.3, 0.5, 1));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(objs.sq, 3));
	// 원기둥
	objs.cy = (t_cylinder*)malloc(sizeof(t_cylinder));
	*(objs.cy) = ft_cylinder_set(ft_vec_set_xyz(0, 10, -1),
							ft_vec_set_xyz(1, 0, 0),
							3, 10, ft_vec_set_xyz(0, 0, 1));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(objs.cy, 4));
	objs.cy = (t_cylinder*)malloc(sizeof(t_cylinder));
	*(objs.cy) = ft_cylinder_set(ft_vec_set_xyz(15, 10, 10),
							ft_vec_set_xyz(0, 0, 1),
							10, 15, ft_vec_set_xyz(1, 0.8, 0.5));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(objs.cy, 4));
	// 삼각형
	objs.tr = (t_triangle*)malloc(sizeof(t_triangle));
	*(objs.tr) = ft_triangle_set(ft_vec_set_xyz(-10, 0, 20),
							ft_vec_set_xyz(10, 0, 20),
							ft_vec_set_xyz(0, 10, 10),
							ft_vec_set_xyz(0.5, 0.5, 1));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(objs.tr, 5));
	objs.tr = (t_triangle*)malloc(sizeof(t_triangle));
	*(objs.tr) = ft_triangle_set(ft_vec_set_xyz(-10, -10, 10),
							ft_vec_set_xyz(10, -10, 0),
							ft_vec_set_xyz(0, 0, 0),
							ft_vec_set_xyz(1, 0, 0));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(objs.tr, 5));
	objs.tr = (t_triangle*)malloc(sizeof(t_triangle));
	*(objs.tr) = ft_triangle_set(ft_vec_set_xyz(20, 40, 0),
							ft_vec_set_xyz(15, 4, -40),
							ft_vec_set_xyz(0, 10, -70),
							ft_vec_set_xyz(0, 1, 0.3));
	ft_hit_lst_addback(&engine.obj_lst, ft_hit_lst_newobj(objs.tr, 5));
	// Camera
	cams.cam = (t_camera*)malloc(sizeof(t_camera));
	*(cams.cam) = ft_camera_set(ft_vec_set_xyz(-20, 20, 20),
						ft_vec_set_xyz(20, -10, -20), 90.0);
	ft_hit_lst_addback(&engine.cam_lst, ft_hit_lst_newobj(cams.cam, 20));
	cams.cam = (t_camera*)malloc(sizeof(t_camera));
	// 카메라 방향벡터가 ft_camera_set()함수의 vup벡터와 동일하면 화면 출력안된다. 나중에 왜그런지 자세히 보자
	*(cams.cam) = ft_camera_set(ft_vec_set_xyz(0, 30, 0),
						ft_vec_set_xyz(0, -1, -0.1), 90.0);
	ft_hit_lst_addback(&engine.cam_lst, ft_hit_lst_newobj(cams.cam, 20));
	cams.cam = (t_camera*)malloc(sizeof(t_camera));
	*(cams.cam) = ft_camera_set(ft_vec_set_xyz(-20, 20, -20),
						ft_vec_set_xyz(1, -1, 1), 90.0);
	ft_hit_lst_addback(&engine.cam_lst, ft_hit_lst_newobj(cams.cam, 20));
	engine.head_cam = engine.cam_lst->content;
//	ft_camera_set(&engine.cam, ft_vec_set_xyz(-20, 20, 20),
//						ft_vec_set_xyz(20, -10, -20), 90.0);
	// Render
	engine.data.mlx = mlx_init();
	engine.data.mlx_win = mlx_new_window(
										engine.data.mlx, engine.data.width,
										engine.data.height, "miniRT");
	tmp_cam_lst = engine.cam_lst;
	while (tmp_cam_lst)
	{
		imgs.img = (t_image*)malloc(sizeof(t_image));
		imgs.img->image = mlx_new_image(engine.data.mlx, engine.data.width,
								engine.data.height);
		imgs.img->address = mlx_get_data_addr(imgs.img->image,
						&engine.data.bits_per_pixel,
						&engine.data.line_length, &engine.data.endian);
		ft_hit_lst_addback(&engine.data.img_lst, ft_hit_lst_newobj(imgs.img, 30));
		tmp_cam_lst = tmp_cam_lst->next;
	}
	engine.data.current_img_lst = engine.data.img_lst;
//	engine.data.img = mlx_new_image(
//						engine.data.mlx, engine.data.width, engine.data.height);
//	engine.data.addr = mlx_get_data_addr(
//								engine.data.img, &engine.data.bits_per_pixel,
//								&engine.data.line_length, &engine.data.endian);

	ft_draw(&engine.data, engine.cam_lst, engine.obj_lst, engine.light_lst);
	mlx_loop_hook(engine.data.mlx, main_loop, &engine);
	mlx_hook(engine.data.mlx_win, KEYPRESS, 1L<<0, ft_key_press, &engine);
//	mlx_hook(engine.data.mlx_win, KEYRELEASE, 1L<<0, ft_key_release, &engine.data);
	mlx_hook(engine.data.mlx_win, X_BTN, 1L<<0, ft_xbtn_click, &engine);
	mlx_loop(engine.data.mlx);
	return (0);
}
