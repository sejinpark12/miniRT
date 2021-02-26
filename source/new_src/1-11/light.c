/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 00:03:51 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/23 22:37:03 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

t_splight	ft_splight_set(t_point3 pos, float intensity, t_color color)
{
	t_splight li;

	li.pos = pos;
	li.intensity = intensity;
	li.color = color;
	return (li);
}

t_spli_info		ft_splight_get_info(t_splight *spli, t_point3 *p)
{
	t_spli_info	spli_info;
	float		r2;

	spli_info.lightdir = ft_vec3_sub(*p, spli->pos);
	r2 = ft_vec3_sqr_len(spli_info.lightdir);
	spli_info.distance = sqrt(r2);
	spli_info.lightdir = ft_vec3_unit_vec(spli_info.lightdir);
	spli_info.lightintensity = ft_vec3_div_f(4 * M_PI * r2,
								ft_vec3_mul_f(spli->intensity, spli->color));
	return (spli_info);
}

t_dilight	ft_dilight_set(t_point3 pos, t_vec3 dir, float intensity, t_color color)
{
	t_dilight dili;

	dili.pos = pos;
	dili.dir = ft_vec3_unit_vec(dir);
	dili.intensity = intensity;
	dili.color = color;
	return (dili);
}