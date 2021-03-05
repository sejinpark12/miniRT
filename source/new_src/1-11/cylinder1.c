/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 22:57:16 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/05 16:08:54 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include <math.h>

t_cylinder	ft_cylinder_set(t_point3 cen, t_vec3 dir, double diameter,
								double h, t_color color)
{
	t_cylinder	cy;

	cy.center = cen;
	cy.dir = ft_vec_unit_vec(dir);
	cy.radius = diameter / 2;
	cy.height = h;
	cy.color = color;
	cy.top_center = ft_vec_add(cy.center,
								ft_vec_mul_f(cy.height / 2, cy.dir));
	cy.bottom_center = ft_vec_sub(cy.center,
								ft_vec_mul_f(cy.height / 2, cy.dir));
	return (cy);
}

//t_cylinder		ft_cylinder_set(const t_cyclinder *cy)
//{
//	return (*cy);
//}

double		ft_cylinder_solve_t(t_cylinder *cy, t_ray *r, t_t *t_range)
{
	t_vec3	oc;
	t_coef	coef;
	t_vec3	ip;
	double	discriminant;
	double	t;

	oc = ft_vec_sub(r->orig, cy->center);
	coef.a = ft_vec_sqr_len(ft_vec_cross(r->dir, cy->dir));
	coef.half_b = ft_vec_dot(ft_vec_cross(r->dir, cy->dir),
			ft_vec_cross(oc, cy->dir));
	coef.c = ft_vec_sqr_len(ft_vec_cross(oc, cy->dir)) - pow(cy->radius, 2.0);
	discriminant = pow(coef.half_b, 2.0) - coef.a * coef.c;
	if (discriminant < 0)
		return (INFINITY);
	t = (-coef.half_b - sqrt(discriminant)) / coef.a;
	ip = ft_ray_at(*r, t);
	if (ft_vec_dot(cy->dir, ft_vec_sub(ip, cy->top_center)) > 0)
		return (INFINITY);
	if (ft_vec_dot(cy->dir, ft_vec_sub(ip, cy->bottom_center)) < 0)
		return (INFINITY);
	if (t <= t_range->min || t_range->max < t)
		return (INFINITY);
	return (t);
}

int			ft_cycap_chk_r(t_ray *r, double t, t_vec3 cap_center, double radius)
{
	if (ft_vec_sqr_len(ft_vec_sub(ft_ray_at(*r, t), cap_center))
			> pow(radius, 2.0))
		return (1);
	else
		return (0);
}

// 원기둥 모자 2개의 각각 t값을 구해서 작은 t값을 얻는 것이 목적
// 모자와의 교차점을 구하는 방법은 평면과 직선의 교차점을 구하는 것과 동일하다.
double		ft_cycap_solve_t(t_cylinder *cy, t_ray *r, t_t *t_range)
{
	t_vec3	top_oc;
	t_vec3	bottom_oc;
	double	denominator;
	double	top_center_t;
	double	bottom_center_t;

	denominator = ft_vec_dot(r->dir, cy->dir);
	if (denominator == 0)
		return (INFINITY);
	top_oc = ft_vec_sub(cy->top_center, r->orig);
	top_center_t = ft_vec_dot(top_oc, cy->dir) / denominator;
	if (ft_cycap_chk_r(r, top_center_t, cy->top_center, cy->radius))
		top_center_t = INFINITY;
	bottom_oc = ft_vec_sub(cy->bottom_center, r->orig);
	bottom_center_t = ft_vec_dot(bottom_oc, cy->dir) / denominator;
	if (ft_cycap_chk_r(r, bottom_center_t, cy->bottom_center, cy->radius))
		bottom_center_t = INFINITY;
	if (top_center_t <= t_range->min || t_range->max < top_center_t)
		top_center_t = INFINITY;
	if (bottom_center_t <= t_range->min || t_range->max < bottom_center_t)
		bottom_center_t = INFINITY;
	if (top_center_t < bottom_center_t)
		return (top_center_t);
	else
		return (bottom_center_t);
}

