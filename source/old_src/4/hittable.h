/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 11:07:29 by sejpark           #+#    #+#             */
/*   Updated: 2020/11/21 13:26:23 by sejpark          ###   ########.fr       */
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

void			set_face_normal(
							t_hit_rec		*rec,
							const t_ray		*r,
							const t_vec3	*outward_normal);
#endif
