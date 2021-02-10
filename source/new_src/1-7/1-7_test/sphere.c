/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:29:38 by sejpark           #+#    #+#             */
/*   Updated: 2020/12/02 17:32:42 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include <math.h>

void			ft_sphere_set(t_sphere *sp, t_point3 *cen, float r)
{
	sp->center = *cen;
	sp->radius = r;
}

int	ft_sphere_hit(t_sphere *sp, t_ray *r, t_t t, t_hit_rec *rec)
{
	t_vec3	oc;
	t_coef	coef;
	float	discriminant;
	float	sqrtd;
	float	root;
	t_vec3	outward_normal;

	ft_vec3_sub(&oc, &r->orig, &sp->center);
	coef.a = ft_vec3_len_sqr(&r->dir);
	coef.half_b = ft_vec3_dot(&oc, &r->dir);
	coef.c = ft_vec3_len_sqr(&oc) - pow(sp->radius, 2.0);
	discriminant = pow(coef.half_b, 2.0) - coef.a * coef.c;
	if (discriminant < 0)
		return (0);
	sqrtd = sqrt(discriminant);
	root = (-coef.half_b - sqrtd) / coef.a;
	if (root < t.min || t.max < root)
	{
		root = (-coef.half_b + sqrtd) / coef.a;
		if (root < t.min || t.max < root)
			return (0);
	}
	rec->t = root;
	ft_ray_at(&rec->p, r, rec->t);
	ft_vec3_sub(&outward_normal, &rec->p, &sp->center);
	ft_vec3_div_float(&outward_normal, sp->radius, &outward_normal);
	ft_set_face_normal(rec, r, &outward_normal);
	return (1);
}
