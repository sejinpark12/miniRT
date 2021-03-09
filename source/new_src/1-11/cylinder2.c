/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 23:59:26 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/09 14:42:46 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"
#include <math.h>

void	ft_cylinder_set_rec(t_cylinder *cy, t_ray *r, t_hit_rec *rec,
				t_cylinder_ts cy_ts)
{
	t_vec3	circle_center; // 교차점 절단면으로 생기는 원의 중심
	t_vec3	outward_normal;

	if (cy_ts.cy_t < cy_ts.cap_t)
	{
		rec->t = cy_ts.cy_t;
		rec->p = ft_ray_at(*r, rec->t);
		circle_center = ft_vec_mul_f(
				ft_vec_dot(cy->dir, ft_vec_sub(rec->p, cy->center)), cy->dir);
		//circle_center는 원기둥의 중심점에서 출발하는 벡터이므로 원기둥의 중심점과 더한다.
		circle_center = ft_vec_add(circle_center, cy->center);
		outward_normal = ft_vec_unit_vec(ft_vec_sub(rec->p, circle_center));
		ft_set_face_normal(rec, r, &outward_normal);
	}
	else
	{
		rec->t = cy_ts.cap_t;
		rec->p = ft_ray_at(*r, rec->t);
		ft_set_face_normal(rec, r, &cy->dir);
	}
	ft_set_hit_rec_color(rec, cy->color);
}

int	ft_cylinder_hit(t_cylinder *cy, t_ray *r, t_t *t_range,
								t_hit_rec *rec)
{
	t_cylinder_ts	cy_ts;

	cy_ts.cy_t = ft_cylinder_solve_t(cy, r, t_range);
	cy_ts.cap_t = ft_cycap_solve_t(cy, r, t_range);
	if (cy_ts.cy_t == INFINITY && cy_ts.cap_t == INFINITY)
		return (0);
	else
	{
		if (cy_ts.cy_t < cy_ts.cap_t)
			t_range->max = cy_ts.cy_t;
		else
			t_range->max = cy_ts.cap_t;
		ft_cylinder_set_rec(cy, r, rec, cy_ts);
		return (1);
	}
}

int	ft_cylinder_sha_hit(t_cylinder *cy, t_ray *r, t_t *t_range)
{
	t_cylinder_ts	cy_ts;

	cy_ts.cy_t = ft_cylinder_solve_t(cy, r, t_range);
	cy_ts.cap_t = ft_cycap_solve_t(cy, r, t_range);
	if (cy_ts.cy_t == INFINITY && cy_ts.cap_t == INFINITY)
		return (0);
	else
		return (1);
}
