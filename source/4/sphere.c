/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:53:50 by sejpark           #+#    #+#             */
/*   Updated: 2020/11/21 13:18:30 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"

void	ft_sphere_set(t_sphere *sp, const t_point3 *cen, const float r)
{
	sp->center = *cen;
	sp->radius = r;
}

int		ft_sphere_hit(t_sphere *sp, const t_ray *r, float t_min, float t_max,
					t_hit_rec *rec)
{
	t_vec3	oc;
	float	a;
	float	half_b;
	float	c;
	float	discriminant;
	float	sqrtd;
	float	root;
	t_vec3	outward_normal;

	ft_vec3_subtract(&oc, r->orig, &(sp->center));
	a = ft_vec3_length_squared(r->dir);
	half_b = ft_vec3_dot(&oc, r->dir);
	c = ft_vec3_length_squared(&oc) - pow(sp->radius, 2.0);
	discriminant = pow(half_b, 2.0) - a * c;
	if (discriminant < 0)
		return (0);
	sqrtd = sqrt(discriminant);
	root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
			return (0);
	}
	rec->t = root;
	ft_ray_at(&(rec->p), r, rec->t);
	ft_vec3_divide_float(&outward_normal, sp->radius,
				ft_vec3_subtract(&outward_normal, &(rec->p), &(sp->center)));
	set_face_normal(rec, r, &outward_normal);
	return (1);
}
