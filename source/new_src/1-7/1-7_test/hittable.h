/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:19:36 by sejpark           #+#    #+#             */
/*   Updated: 2020/12/02 15:58:26 by sejpark          ###   ########.fr       */
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
}				t_hit_rec;

void			ft_set_face_normal(t_hit_rec *rec, t_ray *r,
														t_vec3 *outward_normal);

#endif
