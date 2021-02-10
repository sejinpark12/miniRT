/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:23:19 by sejpark           #+#    #+#             */
/*   Updated: 2020/12/02 15:58:36 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"

void			ft_set_face_normal(t_hit_rec *rec, t_ray *r,
														t_vec3 *outward_normal)
{
	if (ft_vec3_dot(&r->dir, outward_normal) < 0)
		rec->front_face = 1;
	else
		rec->front_face = 0;
	if (rec->front_face == 1)
		rec->normal = *outward_normal;
	else
		ft_vec3_multi_float(&rec->normal, -1, outward_normal);
}
