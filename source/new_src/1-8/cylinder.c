/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 22:57:16 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/11 00:44:00 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include <math.h>

t_cylinder	ft_cylinder_set(t_point3 cen, t_vec3 dir, float r, float h,
								t_color color)
{
	t_cylinder	cy;

	cy.center = cen;
	cy.dir = dir;
	cy.radius = r;
	cy.height = h;
	cy.color = color;
	return (cy);
}

int			ft_cylinder_hit(t_cylinder *cy, t_ray *r, t_t t, t_hit_rec * rec)
{
	t_vec3	oc;
	float	a;
	float	half_b;
	float	c;
	float	discriminant;
	float	root;
	t_vec3	circle_center; // 교차점 절단면으로 생기는 원의 중심
	t_vec3	outward_normal;
	
	oc = ft_vec3_sub(r->orig, cy->center);
	a = ft_vec3_sqr_len(ft_vec3_cross(r->dir, cy->dir));
	half_b = ft_vec3_dot(ft_vec3_cross(r->dir, cy->dir), ft_vec3_cross(oc, cy->dir));
	c = ft_vec3_sqr_len(ft_vec3_cross(oc, cy->dir)) - pow(cy->radius, 2.0);
	if ((discriminant = pow(half_b, 2.0) - a * c) < 0)
		return (0);
	root = (-half_b - sqrt(discriminant)) / a;
	if (root < t.min || t.max < root)
	{
		root = (-half_b + sqrt(discriminant)) / a;
		if (root < t.min || t.max < root)
			return (0);
	}
	rec->t = root;
	rec->p = ft_ray_at(*r, rec->t);
	circle_center = ft_vec3_mul_f(
			ft_vec3_dot(cy->dir, ft_vec3_sub(rec->p, cy->center)), cy->dir);
	outward_normal = ft_vec3_sub(rec->p, circle_center);
	ft_set_face_normal(rec, r, &outward_normal);
	return (1);
}
