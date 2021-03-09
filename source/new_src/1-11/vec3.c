/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 14:27:42 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/09 16:15:48 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_vec3	ft_vec_unit_vec(const t_vec3 v)
{
	return (ft_vec_div_f(ft_vec_len(v), v));
}

t_vec3	ft_vec_set_xyz(const double x, const double y, const double z)
{
	return ((t_vec3){x, y, z});
}

int		create_trgb(const int t, const int r, const int g, const int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
