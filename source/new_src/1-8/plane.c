/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:28:19 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/17 21:54:16 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"
#include <math.h>

extern const float g_pi;

t_plane	ft_plane_set(t_point3 cen, t_vec3 norm, t_color color)
{
	t_plane pl;

	pl.center = cen;
	pl.norm = norm;
	pl.color = color;
	return (pl);
}

float	ft_plane_solve_t(t_plane *pl, t_ray *r)
{
	t_vec3	oc;
	float	denominator;
	float	t;

	denominator = ft_vec3_dot(r->dir, pl->norm);
	if (denominator == 0)
		return (INFINITY);
	oc = ft_vec3_sub(pl->center, r->orig);
	t = ft_vec3_dot(oc, pl->norm) / denominator;
	return (t);
}

int		ft_plane_hit(t_plane *pl, t_ray *r, t_t t_range, t_hit_rec *rec)
{
	t_vec3	ip;
	float	t;

	t = ft_plane_solve_t(pl, r);
	if (t < t_range.min || t_range.max < t)
		return (0);
	rec->t = t;
	ip = ft_vec3_add(r->orig, ft_vec3_mul_f(rec->t, r->dir));
	rec->p = ft_ray_at(*r, rec->t);
	ft_set_face_normal(rec, r, &pl->norm);
	return (1);
}
