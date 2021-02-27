/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:18:00 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/27 17:29:46 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H
# include "hittable.h"

typedef struct	s_plane
{
	t_point3	center;
	t_vec3		norm;
	t_color		color;
}				t_plane;
t_plane			ft_plane_set(t_point3 cen, t_vec3 norm, t_color color);
float			ft_plane_solve_t(t_plane *pl, t_ray *r, t_t t_range);
int				ft_plane_hit(t_plane *pl, t_ray *r, t_t t_range,
													t_hit_rec *rec);
#endif
