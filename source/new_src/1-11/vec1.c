/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:48:09 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/05 16:19:19 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_vec3	ft_vec_add(const t_vec3 u, const t_vec3 v)
{
	return ((t_vec3){u.x + v.x, u.y + v.y, u.z + v.z});
}

t_vec3	ft_vec_sub(const t_vec3 u, const t_vec3 v)
{
	return ((t_vec3){u.x - v.x, u.y - v.y, u.z - v.z});
}

t_vec3	ft_vec_mul(const t_vec3 u, const t_vec3 v)
{
	return ((t_vec3){u.x * v.x, u.y * v.y, u.z * v.z});
}

t_vec3	ft_vec_div(const t_vec3 u, const t_vec3 v)
{
	return ((t_vec3){u.x / v.x, u.y / v.y, u.z / v.z});
}

t_vec3	ft_vec_mul_f(const double t, const t_vec3 v)
{
	return ((t_vec3){v.x * t, v.y * t, v.z * t});
}
