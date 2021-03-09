/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 21:30:20 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/09 15:22:19 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "ray.h"

typedef struct s_cam_scene_data
{
	t_point3	viewpoint;
	t_vec3		dir;
	int			fov;
}				t_cam_scene_data;
typedef struct s_camera
{
	t_point3	origin;
	t_vec3		dir;
	double		cam_phi;
	double		cam_theta;
	t_vec3		w;
	t_vec3		u;
	t_vec3		v;
	t_point3	lower_left_corner;
	t_vec3		horizontal;
	t_vec3		vertical;
}				t_camera;
typedef struct s_cam_data
{
	double		theta;
	double		h;
	double		viewport_h;
	double		viewport_w;
	double		aspect_ratio;
	t_vec3		vup;
}				t_cam_data;
t_camera		ft_camera_set(t_point3 pos, t_vec3 dir, double vfov);
t_ray			ft_camera_get_ray(t_camera *cam, double u, double v);
double			ft_degrees_to_radians(double degrees);
#endif
