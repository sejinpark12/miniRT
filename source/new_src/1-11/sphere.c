/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:29:38 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/05 16:17:19 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include <math.h>

t_sphere	ft_sphere_set(t_point3 cen, double diameter, t_color color)
{
	t_sphere sp;

	sp.center = cen;
	sp.radius = diameter / 2;
	sp.color = color;
	return (sp);
}

double		ft_sphere_solve_t(t_sphere *sp, t_ray *r, t_t *t_range)
{
	t_vec3	oc;
	t_coef	coef;
	double	discriminant;
	double	t;

	oc = ft_vec_sub(r->orig, sp->center);
	coef.a = ft_vec_sqr_len(r->dir);
	coef.half_b = ft_vec_dot(oc, r->dir);
	coef.c = ft_vec_sqr_len(oc) - pow(sp->radius, 2.0);
	discriminant = pow(coef.half_b, 2.0) - coef.a * coef.c;
	if (discriminant < 0)
		return (INFINITY);
	t = (-coef.half_b - sqrt(discriminant)) / coef.a;
	if (t <= t_range->min || t_range->max < t)
	{
		t = (-coef.half_b + sqrt(discriminant)) / coef.a;
		if (t <= t_range->min || t_range->max < t)
			return (INFINITY);
	}
	return (t);
}

int			ft_sphere_hit(t_sphere *sp, t_ray *r, t_t *t_range, t_hit_rec *rec)
{
	double	t;
	t_vec3	outward_normal;

	t = ft_sphere_solve_t(sp, r, t_range);
	if (t != INFINITY)
	{
		t_range->max = t;
		rec->t = t;
		rec->p = ft_ray_at(*r, rec->t);
		outward_normal = ft_vec_div_f(sp->radius,
											ft_vec_sub(rec->p, sp->center));
		ft_set_face_normal(rec, r, &outward_normal);
		ft_set_hit_rec_color(rec, sp->color);
		return (1);
	}
	return (0);
}

int			ft_sphere_sha_hit(t_sphere *sp, t_ray *r, t_t *t_range)
{
	if (ft_sphere_solve_t(sp, r, t_range) != INFINITY)
		return (1);
	else
		return (0);
}
