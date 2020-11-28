/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 20:39:33 by sejpark           #+#    #+#             */
/*   Updated: 2020/11/20 12:07:55 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "vec3.h"
# include "ray.h"

void	ft_ray_set(t_ray *ray, const point3 *origin, const t_vec3 *direction)
{
	ray->orig = (point3*)malloc(sizeof(point3));
	ray->dir = (t_vec3*)malloc(sizeof(t_vec3));
	ft_vec3_set_vec(ray->orig, origin);
	ft_vec3_set_vec(ray->dir, direction);
}
point3	*ft_ray_origin(const t_ray *ray)
{
	return (ray->orig);
}
t_vec3	*ft_ray_direction(const t_ray *ray)
{
	return (ray->dir);
}
point3	*ft_ray_at(point3 *target, const t_ray *ray, float t)
{
	target->e[0] = ray->orig->e[0] + t * ray->dir->e[0];
	target->e[1] = ray->orig->e[1] + t * ray->dir->e[1];
	target->e[2] = ray->orig->e[2] + t * ray->dir->e[2];
	return (target);
}
//point3	*ft_ray_at(const t_ray *ray, float t)
//{
//	point3 *result;
//
//	if (NULL == (result = (point3*)malloc(sizeof(point3))))
//		return (NULL);
//	result->e[0] = ray->orig->e[0] + t * ray->dir->e[0];
//	result->e[1] = ray->orig->e[1] + t * ray->dir->e[1];
//	result->e[2] = ray->orig->e[2] + t * ray->dir->e[2];
//	return (result);
//}
