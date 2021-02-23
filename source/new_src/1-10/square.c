/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 20:44:05 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/23 15:07:13 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "square.h"
#include <math.h>

extern const float g_pi;

t_square	ft_square_set(t_point3 cen, t_vec3 norm, float side_size, t_color color)
{
	t_square sq;

	sq.center = cen;
	sq.norm = ft_vec3_unit_vec(norm);
	sq.side_size = side_size;
	sq.color = color;
	return (sq);
}

float		ft_square_solve_t(t_square *sq, t_ray *r)
{
	t_vec3	oc;
	float	denominator;
	float	t;

	denominator = ft_vec3_dot(r->dir, sq->norm);
	if (denominator == 0)
		return (INFINITY);
	oc = ft_vec3_sub(sq->center, r->orig);
	t = ft_vec3_dot(oc, sq->norm) / denominator;
	return (t);
}

int			ft_square_hit(t_square *sq, t_ray *r, t_t t_range, t_hit_rec *rec)
{
	t_vec3	ip;
	float	t;
	float	cos1;
	float	limit;

	t = ft_square_solve_t(sq, r);
	if (t <= t_range.min || t_range.max < t)
		return (0);
	rec->t = t;
	ip = ft_vec3_add(r->orig, ft_vec3_mul_f(rec->t, r->dir));
	sq->floor = (fabs(sq->norm.y) == 1) ? ft_vec3_set_xyz(1, 0, 0) : ft_vec3_set_xyz(0, 1, 0);
	sq->half_size = ft_vec3_cross(sq->norm, sq->floor);
	sq->center_to_ip = ft_vec3_sub(ip, sq->center);
	cos1 = fabs(ft_vec3_dot(sq->half_size, sq->center_to_ip)
				/ (ft_vec3_len(sq->half_size) * ft_vec3_len(sq->center_to_ip)));
	if (cos1 < sqrt(2) / 2)
		cos1 = cos(M_PI_2 - acos(cos1));
	limit = (sq->side_size / 2) / cos1;
	if (sqrt(ft_vec3_dot(sq->center_to_ip, sq->center_to_ip)) <= limit)
	{
		rec->p = ft_ray_at(*r, rec->t);
		ft_set_face_normal(rec, r, &sq->norm);
		ft_set_hit_rec_color(rec, sq->color);
		return (1);
	}
	return (0);
}
