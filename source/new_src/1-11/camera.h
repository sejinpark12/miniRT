/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 21:30:20 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/03 16:54:59 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "random.h"
# include "ray.h"

typedef struct	s_camera
{
	t_point3	origin;
	t_vec3		dir;
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
typedef	struct	s_cam_data
{
	float		theta;
	float		h;
	float		viewport_h;
	float		viewport_w;
	float		aspect_ratio;
	t_vec3		vup;
}				t_cam_data;
//t_camera		*ft_camera_set(t_camera *cam, t_point3 lookfrom,
//								t_point3 lookat, t_vec3 vup,
//								float vfov, float aspect_ratio);
t_camera		ft_camera_set(t_point3 pos, t_vec3 dir, float vfov);
t_ray			ft_camera_get_ray(t_camera *cam, float u, float v);
float			ft_degrees_to_radians(float degrees);
#endif
