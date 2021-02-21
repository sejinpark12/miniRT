/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:18:00 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/17 21:54:27 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H
# include "hittable.h"
# include "vec3.h"

typedef struct	s_plane
{
	t_point3	center;
	t_vec3		norm;
	t_color		color;
}				t_plane;
t_plane			ft_plane_set(t_point3 cen, t_vec3 norm, t_color color);
float			ft_plane_solve_t(t_plane *pl, t_ray *r);
int				ft_plane_hit(t_plane *pl, t_ray *r, t_t t_range, t_hit_rec *rec);
#endif
