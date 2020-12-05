/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 22:41:59 by sejpark           #+#    #+#             */
/*   Updated: 2020/12/05 23:34:55 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_camera.h"
#include "vec3.h"

t_camera *ft_camera_set(t_camera *target)
{
	float aspect_ratio;
	float viewport_height;
	float viewport_width;
	float focal_length;

	aspect_ratio = 16.0 / 9.0;
	viewport_height = 2.0;
	viewport_width = aspect_ratio * viewport_height;
	focal_length = 1.0;
	ft_vec3_set_xyz(&target->origin, 0, 0, 0);
	ft_vec3_set_xyz(&target->horizontal, viewport_width, 0.0, 0.0);
	ft_vec3_set_xyz(&target->vertical, 0.0, viewport_height, 0.0);
	target->lower_left_corner.x = target->origin.x - target->horizontal.x / 2
									- target->vertical.x / 2 - 0;
	target->lower_left_corner.y = target->origin.y - target->horizontal.y / 2
									- target->vertical.y / 2 - 0;
	target->lower_left_corner.z = target->origin.z - target->horizontal.z / 2
									- target->vertical.z / 2 - focal_length;
	return (target);
}

t_ray *ft_camera_get_ray(t_ray *target, t_camera *cam, float u, float v)
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
