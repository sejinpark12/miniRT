/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 21:01:31 by sejpark           #+#    #+#             */
/*   Updated: 2020/11/24 12:58:34 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H
# include "vec3.h"
# include <stdlib.h>

typedef	t_vec3	t_point3;
typedef struct	s_ray
{
	t_point3	*orig;
	t_vec3		*dir;
}				t_ray;
t_point3		*ft_ray_origin(const t_ray *ray);
t_vec3			*ft_ray_direction(const t_ray *ray);
void			ft_ray_set(
							t_ray			*ray,
							const t_point3	*origin,
							const t_vec3	*direction);
t_point3		*ft_ray_at(
							t_point3		*target,
							const t_ray		*ray,
							float			t);
#endif
