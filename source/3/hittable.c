/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:42:37 by sejpark           #+#    #+#             */
/*   Updated: 2020/11/20 19:51:22 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"

void			set_face_normal(t_hit_rec *rec, const t_ray *r, const t_vec3 *outward_normal)
{
	t_vec3 tmp;
	if (ft_vec3_dot(r->dir, outward_normal) < 0)
		rec->front_face = 1;
	else
		rec->front_face = 0;
	if (rec->front_face)
		rec->normal = *outward_normal;
	else
		rec->normal = *ft_vec3_multiply_float(&tmp, -1, outward_normal);
}
