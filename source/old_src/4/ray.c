/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:39:33 by sejpark           #+#    #+#             */
/*   Updated: 2020/11/21 13:14:04 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "ray.h"

t_point3	*ft_ray_origin(const t_ray *ray)
{
	return (ray->orig);
}

t_vec3		*ft_ray_direction(const t_ray *ray)
{
	return (ray->dir);
}

void		ft_ray_set(t_ray *ray, const t_point3 *origin,
													const t_vec3 *direction)
{
	ray->orig = (t_point3*)malloc(sizeof(t_point3));
	ray->dir = (t_vec3*)malloc(sizeof(t_vec3));
	ft_vec3_set_vec(ray->orig, origin);
	ft_vec3_set_vec(ray->dir, direction);
}

t_point3	*ft_ray_at(t_point3 *target, const t_ray *ray, float t)
{
	target->e[0] = ray->orig->e[0] + t * ray->dir->e[0];
	target->e[1] = ray->orig->e[1] + t * ray->dir->e[1];
	target->e[2] = ray->orig->e[2] + t * ray->dir->e[2];
	return (target);
}
