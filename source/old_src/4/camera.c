/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:04:54 by sejpark           #+#    #+#             */
/*   Updated: 2020/11/24 19:36:19 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void	ft_camera_set(t_camera *camera)
{
	float aspect_ratio;
	float viewport_height;
	float focal_length;
	float viewport_width;

	aspect_ratio= 16.0 / 9.0;
	viewport_height = 2.0;
	viewport_width= aspect_ratio * viewport_height;
	focal_length= 1.0;
	ft_vec3_set_rgb(&camera->origin, 0, 0, 0);
	ft_vec3_set_rgb(&camera->horizontal, viewport_width, 0.0, 0.0);
	ft_vec3_set_rgb(&camera->vertical, 0.0, viewport_height, 0.0);
	camera->lower_left_corner.e[0] = camera->origin.e[0]
								- (camera->horizontal.e[0] / 2)
								- (camera->vertical.e[0] / 2) - 0; 
	camera->lower_left_corner.e[1] = camera->origin.e[1]
								- (camera->horizontal.e[1] / 2)
								- (camera->vertical.e[1] / 2) - 0; 
	camera->lower_left_corner.e[2] = camera->origin.e[2]
								- (camera->horizontal.e[2] / 2)
								- (camera->vertical.e[2] / 2) - focal_length; 
}

t_ray	*ft_get_ray(t_ray *target, t_camera *camera, float u, float v)
{
	t_vec3 ray_set_cal;

	ray_set_cal.e[0] = camera->lower_left_corner.e[0]
						+ u * camera->horizontal.e[0]
						+ v * camera->vertical.e[0]
						- camera->origin.e[0];
	ray_set_cal.e[1] = camera->lower_left_corner.e[1]
						+ u * camera->horizontal.e[1]
						+ v * camera->vertical.e[1]
						- camera->origin.e[1];
	ray_set_cal.e[2] = camera->lower_left_corner.e[2]
						+ u * camera->horizontal.e[2]
						+ v * camera->vertical.e[2]
						- camera->origin.e[2];
	ft_ray_set(target, &camera->origin, &ray_set_cal);
	return (target);
}
