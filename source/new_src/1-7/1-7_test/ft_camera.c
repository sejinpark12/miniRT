/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 22:41:59 by sejpark           #+#    #+#             */
/*   Updated: 2021/01/31 23:50:33 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_camera.h"
#include "vec3.h"
#include <math.h>
#include <stdio.h>

const float	g_pi = 3.1415926535897932385;

/* *********************************** 수정 ********************************* */
t_camera		*ft_camera_set(t_camera *target, t_point3 *lookfrom,
								t_point3 *lookat, t_vec3 *vup,
								float vfov, float aspect_ratio)
{
	float	theta;
	float	h;
	float	viewport_height;
	float	viewport_width;

	theta = ft_degrees_to_radians(vfov);
	h = tan(theta / 2);
	viewport_height = 2.0 * h;
	viewport_width = aspect_ratio * viewport_height;
	ft_vec3_unit_vec(&target->w, ft_vec3_sub(&target->w, lookfrom, lookat));
	ft_vec3_unit_vec(&target->u, ft_vec3_cross(&target->u, vup, &target->w));
	ft_vec3_cross(&target->v, &target->w, &target->u);

	ft_vec3_set_xyz(&target->origin, lookfrom->x, lookfrom->y, lookfrom->z);
	ft_vec3_multi_float(&target->horizontal, viewport_width, &target->u);
	ft_vec3_multi_float(&target->vertical, viewport_height, &target->v);
	target->lower_left_corner.x = target->origin.x - target->horizontal.x / 2
									- target->vertical.x / 2 - target->w.x;
	target->lower_left_corner.y = target->origin.y - target->horizontal.y / 2
									- target->vertical.y / 2 - target->w.y;
	target->lower_left_corner.z = target->origin.z - target->horizontal.z / 2
									- target->vertical.z / 2 - target->w.z;
	printf("lower_left_corner: x = %f, y = %f, z = %f\n",
			target->lower_left_corner.x, target->lower_left_corner.y, target->lower_left_corner.z);
	printf("w : x = %f, y = %f, z = %f\n", target->w.x, target->w.y, target->w.z);
	printf("u : x = %f, y = %f, z = %f\n", target->u.x, target->u.y, target->u.z);
	return (target);
}
/* ************************************************************************** */

t_ray		*ft_camera_get_ray(t_ray *target, t_camera *cam, float u, float v)
{
	t_vec3 tmp;

	tmp.x = cam->lower_left_corner.x + u * cam->horizontal.x
			+ v * cam->vertical.x - cam->origin.x;
	tmp.y = cam->lower_left_corner.y + u * cam->horizontal.y
			+ v * cam->vertical.y - cam->origin.y;
	tmp.z = cam->lower_left_corner.z + u * cam->horizontal.z
			+ v * cam->vertical.z - cam->origin.z;
	ft_ray_set(target, &(cam->origin), &tmp);	
	return (target);
}

float		ft_degrees_to_radians(float degrees)
{
	return (degrees * g_pi / 180.0);
}
