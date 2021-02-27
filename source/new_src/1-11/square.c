/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 20:44:05 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/27 17:36:52 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "square.h"
#include <math.h>

extern const float g_pi;

t_square	ft_square_set(t_point3 cen, t_vec3 norm, float side_size,
							t_color color)
{
	t_square sq;

	sq.sq_plane = ft_plane_set(cen, norm, color);
	sq.side_size = side_size;
	return (sq);
}

float		ft_square_solve_t(t_square *sq, t_ray *r, t_t t_range)
{
	return (ft_plane_solve_t(&sq->sq_plane, r, t_range));
}

int			ft_square_set_rec(t_square *sq, t_ray *r, t_hit_rec *rec, float t)
{
	t_vec3	ip;
	float	cos1;
	float	limit;

	rec->t = t;
	ip = ft_vec_add(r->orig, ft_vec_mul_f(rec->t, r->dir));
	if (fabs(sq->sq_plane.norm.y) == 1)
		sq->floor = ft_vec_set_xyz(1, 0, 0);
	else
		sq->floor = ft_vec_set_xyz(0, 1, 0);
	sq->half_size = ft_vec_cross(sq->sq_plane.norm, sq->floor);
	sq->center_to_ip = ft_vec_sub(ip, sq->sq_plane.center);
	cos1 = fabs(ft_vec_dot(sq->half_size, sq->center_to_ip)
				/ (ft_vec_len(sq->half_size) * ft_vec_len(sq->center_to_ip)));
	if (cos1 < sqrt(2) / 2)
		cos1 = cos(M_PI_2 - acos(cos1));
	limit = (sq->side_size / 2) / cos1;
	if (sqrt(ft_vec_dot(sq->center_to_ip, sq->center_to_ip)) <= limit)
	{
		rec->p = ft_ray_at(*r, rec->t);
		ft_set_face_normal(rec, r, &sq->sq_plane.norm);
		ft_set_hit_rec_color(rec, sq->sq_plane.color);
		return (1);
	}
	return (0);
}

int			ft_square_hit(t_square *sq, t_ray *r, t_t t_range, t_hit_rec *rec)
{
	float	t;

	t = ft_square_solve_t(sq, r, t_range);
	if (t == INFINITY)
		return (0);
	else
		return (ft_square_set_rec(sq, r, rec, t));
}
