/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:36:34 by sejpark           #+#    #+#             */
/*   Updated: 2020/11/26 19:47:35 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_ray		*ft_ray_set(t_ray *target, t_point3 *origin, t_vec3 *direction)
{
	target->orig = *origin;
	target->dir = *direction;
	return (target);
}

t_point3	*ft_ray_at(t_point3 *target, t_ray *ray, float t)
{
	target->x = ray->orig.x + t * ray->dir.x;
	target->y = ray->orig.y + t * ray->dir.y;
	target->z = ray->orig.z + t * ray->dir.z;
	return (target);
}
