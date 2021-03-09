/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 22:41:59 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/09 14:08:35 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include <math.h>

const double	g_pi = 3.1415926535897932385;

t_camera	ft_camera_set(t_point3 pos, t_vec3 dir, double vfov)
{
	t_camera	cam;
	t_cam_data	cam_data;

	cam_data.aspect_ratio = 16.0 / 9.0;
	cam_data.vup = ft_vec_set_xyz(0, 1, 0);
	cam_data.theta = ft_degrees_to_radians(vfov);
	cam_data.h = tan(cam_data.theta / 2);
	cam_data.viewport_h = 2.0 * cam_data.h;
	cam_data.viewport_w = cam_data.aspect_ratio * cam_data.viewport_h;
	cam.w = ft_vec_unit_vec(ft_vec_mul_f(-1, dir));
	cam.u = ft_vec_unit_vec(ft_vec_cross(cam_data.vup, cam.w));
	cam.v = ft_vec_cross(cam.w, cam.u);
	cam.origin = pos;
	cam.dir = dir;
	cam.horizontal = ft_vec_mul_f(cam_data.viewport_w, cam.u);
	cam.vertical = ft_vec_mul_f(cam_data.viewport_h, cam.v);
	cam.lower_left_corner = ft_vec_set_xyz(
			cam.origin.x - cam.horizontal.x / 2 - cam.vertical.x / 2 - cam.w.x,
			cam.origin.y - cam.horizontal.y / 2 - cam.vertical.y / 2 - cam.w.y,
			cam.origin.z - cam.horizontal.z / 2 - cam.vertical.z / 2 - cam.w.z);
	return (cam);
}

/* ************************************************************************** */

// 매개변수를 t_camera cam로 하면 render.c 파일의 ft_draw 함수에서 ft_camera_get_ray 함수를 호출할 때 첫번째 매개변수의 타입이 t_camera cam로 되어 있으므로 void*형의 content 변수를 t_camera *로 바꿔주고 역참조를 해야한다. 굳이 이렇게 보기힘들고 불편하기 할 필요가 없으므로 ft_camera_get_ray의 첫번째 매개변수를 t_camera *형으로 바꾸어서 ft_camera_get_ray를 호출할때 매개변수가 자동으로 void*형에서 t_camera*형으로 대입되게 한다.

//t_ray		ft_camera_get_ray(t_camera cam, double u, double v)

t_ray	ft_camera_get_ray(t_camera *cam, double u, double v)
{
	t_vec3	dir;

	dir.x = cam->lower_left_corner.x + u * cam->horizontal.x
		+ v * cam->vertical.x - cam->origin.x;
	dir.y = cam->lower_left_corner.y + u * cam->horizontal.y
		+ v * cam->vertical.y - cam->origin.y;
	dir.z = cam->lower_left_corner.z + u * cam->horizontal.z
		+ v * cam->vertical.z - cam->origin.z;
	return (ft_ray_set(cam->origin, ft_vec_unit_vec(dir)));
}

double	ft_degrees_to_radians(double degrees)
{
	return (degrees * g_pi / 180.0);
}
