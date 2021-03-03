/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:28:19 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/01 19:53:54 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"
#include <math.h>

extern const float g_pi;

t_plane	ft_plane_set(t_point3 cen, t_vec3 norm, t_color color)
{
	t_plane	pl;

	pl.center = cen;
	pl.norm = ft_vec_unit_vec(norm);
	pl.color = color;
	return (pl);
}

float	ft_plane_solve_t(t_plane *pl, t_ray *r, t_t *t_range)
{
	t_vec3	oc;
	float	denominator;
	float	t;

	denominator = ft_vec_dot(r->dir, pl->norm);
	if (denominator == 0)
		return (INFINITY);
	oc = ft_vec_sub(pl->center, r->orig);
	t = ft_vec_dot(oc, pl->norm) / denominator;
	if (t <= t_range->min || t_range->max < t)
		return(INFINITY);
	return (t);
}

int		ft_plane_hit(t_plane *pl, t_ray *r, t_t *t_range, t_hit_rec *rec)
{
	float	t;

	t = ft_plane_solve_t(pl, r, t_range);
	if (t == INFINITY)
		return (0);
	t_range->max = t;
	rec->t = t;
	rec->p = ft_ray_at(*r, rec->t);
	ft_set_face_normal(rec, r, &pl->norm);
	ft_set_hit_rec_color(rec, pl->color);
	return (1);
}

int		ft_plane_sha_hit(t_plane *pl, t_ray *r, t_t *t_range)
{
	if (ft_plane_solve_t(pl, r, t_range) == INFINITY)
		return (0);
	else
		return (1);
}
