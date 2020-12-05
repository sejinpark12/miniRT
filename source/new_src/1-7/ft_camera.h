/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 21:30:20 by sejpark           #+#    #+#             */
/*   Updated: 2020/12/05 23:35:07 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CAMERA_H
# define FT_CAMERA_H
# include "ft_random.h"
# include "vec3.h"
# include "ray.h"

typedef struct	s_camera
{
	t_point3	origin;
	t_point3	lower_left_corner;
	t_vec3		horizontal;
	t_vec3		vertical;
}				t_camera;
t_camera		*ft_camera_set(t_camera *target);
t_ray			*ft_camera_get_ray(t_ray *target, t_camera *cam, float u,
																	float v);
#endif
