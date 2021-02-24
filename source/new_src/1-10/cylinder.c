/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 22:57:16 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/24 17:31:56 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include <math.h>
#include <stdio.h>

//t_cylinder	ft_cylinder_set(t_point3 cen, t_vec3 dir, float diameter, float h,
//								t_color color)
//{
//	t_cylinder	cy;
//
//	cy.center = cen;
//	cy.dir = ft_vec3_unit_vec(dir);
//	cy.radius = diameter / 2;
//	cy.height = h;
//	cy.color = color;
//	cy.top_center = ft_vec3_add(cy.center, ft_vec3_mul_f(cy.height / 2, cy.dir));
//	cy.bottom_center = ft_vec3_sub(cy.center, ft_vec3_mul_f(cy.height / 2, cy.dir));
//	return (cy);
//}

t_cylinder		ft_cylinder_set(const t_cyclinder *cy)
{
	return (*cy);
}

float		ft_cylinder_solve_t(t_cylinder *cy, t_ray *r, t_t t_range)
{
	t_vec3	oc;
	t_coef	coef;
	t_vec3	ip;
	float	discriminant;
	float	t;
	//t_vec3	circle_center; // 교차점 절단면으로 생기는 원의 중심

//	printf("dir_x = %f, y = %f, z = %f \n", cy->dir.x, cy->dir.y, cy->dir.z);
//	printf("top_x = %f, y = %f, z = %f \n", cy->top_center.x, cy->top_center.y, cy->top_center.z);
//	printf("bottom_x = %f, y = %f, z = %f \n", cy->bottom_center.x, cy->bottom_center.y, cy->bottom_center.z);
	oc = ft_vec3_sub(r->orig, cy->center);
	coef.a = ft_vec3_sqr_len(ft_vec3_cross(r->dir, cy->dir));
	coef.half_b = ft_vec3_dot(
								ft_vec3_cross(r->dir, cy->dir),
								ft_vec3_cross(oc, cy->dir));
	coef.c = ft_vec3_sqr_len(ft_vec3_cross(oc, cy->dir)) - pow(cy->radius, 2.0);
	if ((discriminant = pow(coef.half_b, 2.0) - coef.a * coef.c) < 0)
		return (INFINITY);
	t = (-coef.half_b - sqrt(discriminant)) / coef.a;
	ip = ft_ray_at(*r, t);
//	circle_center = ft_vec3_mul_f(
//			ft_vec3_dot(cy->dir, ft_vec3_sub(ip, cy->center)), cy->dir);
//	//circle_center는 원기둥의 중심점에서 출발하는 벡터이므로 원기둥의 중심점과 더한다.
//	circle_center = ft_vec3_add(circle_center, cy->center);
//	if (t < t_range.min || t_range.max < t
//		|| ft_vec3_len(ft_vec3_sub(circle_center, cy->center)) > cy->height / 2)
//	{
//		t = (-coef.half_b + sqrt(discriminant)) / coef.a;
//		ip = ft_ray_at(*r, t);
//		circle_center = ft_vec3_mul_f(
//				ft_vec3_dot(cy->dir, ft_vec3_sub(ip, cy->center)), cy->dir);
//		//circle_center는 원기둥의 중심점에서 출발하는 벡터이므로 원기둥의 중심점과 더한다.
//		circle_center = ft_vec3_add(circle_center, cy->center);
//		if (t < t_range.min || t_range.max < t
//		|| ft_vec3_len(ft_vec3_sub(circle_center, cy->center)) > cy->height / 2)
//			return (INFINITY);
//	}
	if (ft_vec3_dot(cy->dir, ft_vec3_sub(ip, cy->top_center)) > 0)
		return (INFINITY);
	if (ft_vec3_dot(cy->dir, ft_vec3_sub(ip, cy->bottom_center)) < 0)
		return (INFINITY);
	if (t <= t_range.min || t_range.max < t)
	{
		t = (-coef.half_b + sqrt(discriminant)) / coef.a;
		ip = ft_ray_at(*r, t);
		if (t <= t_range.min || t_range.max < t)
			return (INFINITY);
	}
	return (t);
}

float	ft_cycap_solve_t(t_cylinder *cy, t_ray *r, t_t t_range)
{
	// 원기둥 모자 2개의 각각 t값을 구해서 작은 t값을 얻는 것이 목적
	// 모자와의 교차점을 구하는 방법은 평면과 직선의 교차점을 구하는 것과 동일하다.
	t_vec3	top_oc;
	t_vec3	bottom_oc;
	float	denominator;
	float	top_center_t;
	float	bottom_center_t;

	denominator = ft_vec3_dot(r->dir, cy->dir);
	if (denominator == 0)
		return (INFINITY);
	top_oc = ft_vec3_sub(cy->top_center, r->orig);
	top_center_t = ft_vec3_dot(top_oc, cy->dir) / denominator;
	if (ft_vec3_sqr_len(ft_vec3_sub(ft_ray_at(*r, top_center_t), cy->top_center))
																> pow(cy->radius, 2.0))
		top_center_t = INFINITY;
	bottom_oc = ft_vec3_sub(cy->bottom_center, r->orig);
	bottom_center_t = ft_vec3_dot(bottom_oc, cy->dir) / denominator;
	if (ft_vec3_sqr_len(ft_vec3_sub(ft_ray_at(*r, bottom_center_t), cy->bottom_center))
																> pow(cy->radius, 2.0))
		bottom_center_t = INFINITY;
	if (top_center_t <= t_range.min || t_range.max < top_center_t)
		top_center_t = INFINITY;
	if (bottom_center_t <= t_range.min || t_range.max < bottom_center_t)
		bottom_center_t = INFINITY;
	return (top_center_t < bottom_center_t ? top_center_t : bottom_center_t);
}

int			ft_cylinder_hit(t_cylinder *cy, t_ray *r, t_t t_range,
							t_hit_rec * rec)
{
	float	cy_t;
	float	cap_t;
	t_vec3	circle_center; // 교차점 절단면으로 생기는 원의 중심
	t_vec3	outward_normal;
	
	cy_t = ft_cylinder_solve_t(cy, r, t_range);
	cap_t = ft_cycap_solve_t(cy, r, t_range);
	if (cy_t != INFINITY && cy_t < cap_t)
	{
		rec->t = cy_t;
		rec->p = ft_ray_at(*r, rec->t);
		circle_center = ft_vec3_mul_f(
				ft_vec3_dot(cy->dir, ft_vec3_sub(rec->p, cy->center)), cy->dir);
		//circle_center는 원기둥의 중심점에서 출발하는 벡터이므로 원기둥의 중심점과 더한다.
		circle_center = ft_vec3_add(circle_center, cy->center);
//		if (ft_vec3_len(ft_vec3_sub(circle_center, cy->center)) > cy->height / 2)
//			return (0);
		outward_normal = ft_vec3_unit_vec(ft_vec3_sub(rec->p, circle_center));
		ft_set_face_normal(rec, r, &outward_normal);
		ft_set_hit_rec_color(rec, cy->color);
		return (1);
	}
	else if (cap_t != INFINITY && cap_t < cy_t)
	{
		rec->t = cap_t;
		rec->p = ft_ray_at(*r, rec->t);
		ft_set_face_normal(rec, r, &cy->dir);
		ft_set_hit_rec_color(rec, cy->color);
		return (1);
	}
	return (0);
}
