/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 21:30:20 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/10 00:16:26 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CAMERA_H
# define FT_CAMERA_H
# include "ft_random.h"
# include "vec3.h"
# include "ray.h"

typedef struct	s_camera
{
	t_vec3		lookfrom;
	t_vec3		lookat;
	t_vec3		vup;
	t_point3	origin;
// 21.01.30 코드 추가////////////
	float		cam_phi;
	float		cam_theta;
	t_vec3		w;
	t_vec3		u;
	t_vec3		v;
/////////////////////////////////
	t_point3	lower_left_corner;
	t_vec3		horizontal;
	t_vec3		vertical;
}				t_camera;
t_camera		*ft_camera_set(t_camera *cam, t_point3 lookfrom,
								t_point3 lookat, t_vec3 vup,
								float vfov, float aspect_ratio);
t_ray			ft_camera_get_ray(t_camera cam, float u, float v);
float			ft_degrees_to_radians(float degrees);
#endif
