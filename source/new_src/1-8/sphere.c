/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:29:38 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/10 15:00:21 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include <math.h>

t_sphere	ft_sphere_set(t_point3 cen, float r)
{
	t_sphere sp;

	sp.center = cen;
	sp.radius = r;
	return (sp);
}

int			ft_sphere_hit(t_sphere *sp, t_ray *r, t_t t, t_hit_rec *rec)
{
	t_vec3	oc;
	t_coef	coef;
	float	discriminant;
	float	root;
	t_vec3	outward_normal;

	oc = ft_vec3_sub(r->orig, sp->center);
	coef.a = ft_vec3_sqr_len(r->dir);
	coef.half_b = ft_vec3_dot(oc, r->dir);
	coef.c = ft_vec3_sqr_len(oc) - pow(sp->radius, 2.0);
	if ((discriminant = pow(coef.half_b, 2.0) - coef.a * coef.c) < 0)
		return (0);
	root = (-coef.half_b - sqrt(discriminant)) / coef.a;
	if (root < t.min || t.max < root)
	{
		root = (-coef.half_b + sqrt(discriminant)) / coef.a;
		if (root < t.min || t.max < root)
			return (0);
	}
	rec->t = root;
	rec->p = ft_ray_at(*r, rec->t);
	outward_normal = ft_vec3_div_f(sp->radius, ft_vec3_sub(rec->p, sp->center));
	ft_set_face_normal(rec, r, &outward_normal);
	return (1);
}
