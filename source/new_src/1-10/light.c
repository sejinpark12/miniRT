/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 00:03:51 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/23 01:31:45 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

t_splight	ft_light_set(t_point3 pos, float intensity, t_color color)
{
	t_splight li;

	li.pos = pos;
	li.intensity = intensity;
	li.color = color;
	return (li);
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
