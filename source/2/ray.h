/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 21:01:31 by sejpark           #+#    #+#             */
/*   Updated: 2020/11/19 19:31:54 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H
# include "vec3.h"

typedef t_vec3 point3;
typedef struct	s_ray
{
	point3		*orig;
	t_vec3		*dir;
}				t_ray;
void	ft_ray_set(t_ray *ray, const point3 *origin, const t_vec3 *direction);
point3	*ft_ray_origin(const t_ray *ray);
t_vec3	*ft_ray_direction(const t_ray *ray);
point3	*ft_ray_at(point3 *target, const t_ray *ray, float t);
//point3	*ft_ray_at(const t_ray *ray, float t);

#endif
