/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:19:36 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/23 12:30:56 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_H
# define HITTABLE_H
# include "ray.h"

typedef struct	s_hit_rec
{
	t_point3	p;
	t_vec3		normal;
	float		t;
	int			front_face;
	t_color		color;
}				t_hit_rec;

void			ft_set_face_normal(t_hit_rec *rec, t_ray *r,
														t_vec3 *outward_normal);
void			ft_set_hit_rec_color(t_hit_rec *rec, t_color color);
void			ft_reset_hit_rec(t_hit_rec *rec);
#endif
