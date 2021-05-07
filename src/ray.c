/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:36:34 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/09 16:14:51 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_ray		ft_ray_set(t_point3 origin, t_vec3 direction)
{
	t_ray	target;

	target.orig = origin;
	target.dir = direction;
	return (target);
}

t_point3	ft_ray_at(t_ray ray, double t)
{
	t_point3	target;

	target = ft_vec_set_xyz(
			ray.orig.x + t * ray.dir.x,
			ray.orig.y + t * ray.dir.y,
			ray.orig.z + t * ray.dir.z);
	return (target);
}
