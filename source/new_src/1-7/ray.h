/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:29:52 by sejpark           #+#    #+#             */
/*   Updated: 2020/11/26 19:43:09 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H
# include "vec3.h"

typedef struct	s_ray
{
	t_point3	orig;		
	t_vec3		dir;
}				t_ray;
t_ray			*ft_ray_set(t_ray *target, t_point3 *origin, t_vec3 *direction);
t_point3		*ft_ray_at(t_point3 *target, t_ray *ray, float t);
#endif
