/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:57:10 by sejpark           #+#    #+#             */
/*   Updated: 2020/11/24 19:33:21 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

#include "minirt.h"

typedef struct	s_camera
{
	t_point3	origin;
	t_point3	lower_left_corner;
	t_vec3		horizontal;
	t_vec3		vertical;
	float		aspect_ratio;
	int			image_width;
	int			image_height;
	int			samples_per_pixel;
}				t_camera;
void			ft_camera_set(t_camera *camera);
t_ray			*ft_get_ray(t_ray *target, t_camera *camera, float u, float v);

#endif
