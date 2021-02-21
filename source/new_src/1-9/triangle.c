/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:45:01 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/22 01:22:39 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "triangle.h"
#include <stdio.h> 

t_triangle		ft_triangle_set(t_point3 p0, t_point3 p1, t_point3 p2,
															t_color color)
{
	t_triangle tr;

	tr.p0 = p0;
	tr.p1 = p1;
	tr.p2 = p2;
	tr.tr_plane.center = p0; // 평면과 직선의 교차점을 구하기 위한 과정중 t를 구하기 위해서는 평면상의 한점 아무거나 필요하다. 평면을 구할 때는 그 점을 중점으로 사용했지만 삼각형에서는 p0을 사용하기로 했다.
	tr.tr_plane.color = color;
	tr.tr_plane.norm = ft_vec3_cross(ft_vec3_sub(p1, p0), ft_vec3_sub(p2, p0));
	tr.edge0 = ft_vec3_sub(p1, p0);
	tr.edge1 = ft_vec3_sub(p2, p1);
	tr.edge2 = ft_vec3_sub(p0, p2);
	return (tr);
}

void			ft_triangle_set_c(t_triangle *tr, t_point3 p)
{
	tr->c0 = ft_vec3_sub(p, tr->p0);
	tr->c1 = ft_vec3_sub(p, tr->p1);
	tr->c2 = ft_vec3_sub(p, tr->p2);
}

float			ft_triangle_solve_t(t_triangle *tr, t_ray *r)
{
	return (ft_plane_solve_t(&tr->tr_plane, r));
}

int				ft_triangle_hit(t_triangle *tr, t_ray *r, t_t t_range,
															t_hit_rec *rec)
{
	float	t;

	t = ft_triangle_solve_t(tr, r);
	if (t < t_range.min || t_range.max < t)
		return (0);
	ft_triangle_set_c(tr, ft_ray_at(*r, t));
	if (ft_vec3_dot(tr->tr_plane.norm, ft_vec3_cross(tr->edge0, tr->c0)) > 0 &&
			ft_vec3_dot(tr->tr_plane.norm, ft_vec3_cross(tr->edge1, tr->c1)) > 0 &&
			ft_vec3_dot(tr->tr_plane.norm, ft_vec3_cross(tr->edge2, tr->c2)) > 0)
	{
		rec->t = t;
		rec->p = ft_ray_at(*r, rec->t);
		ft_set_face_normal(rec, r, &tr->tr_plane.norm);
		return (1);
	}
	return (0);	
}
