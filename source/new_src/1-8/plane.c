/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:28:19 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/10 14:59:25 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"
#include <math.h>
#include <stdio.h>

t_plane	ft_plane_set(t_point3 cen, t_vec3 norm, t_color color)
{
	t_plane pl;

	pl.center = cen;
	pl.norm_vec = norm;
	pl.color = color;
	return (pl);
}

int		ft_plane_hit(t_plane *pl, t_ray *r, t_t t, t_hit_rec *rec)
{
	t_vec3	oc;
	t_vec3	d;
	float	root;

	oc = ft_vec3_sub(pl->center, r->orig);
	if (ft_vec3_dot(r->dir, pl->norm_vec) == 0)
		return (0);
	root = ft_vec3_dot(oc, pl->norm_vec) / ft_vec3_dot(r->dir, pl->norm_vec);
	if (root < t.min || t.max < root)
		return (0);
	rec->t = root;
	d = ft_vec3_add(r->orig, ft_vec3_mul_f(rec->t, r->dir));
	if (fabs(d.x - pl->center.x) > 4)
		return (0);
	if (fabs(d.y - pl->center.y) > 4)
		return (0);
	if (fabs(d.z - pl->center.z) > 4)
		return (0);
	rec->p = ft_ray_at(*r, rec->t);
	ft_set_face_normal(rec, r, &pl->norm_vec);
	return (1);
}
