/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 14:24:41 by sejpark           #+#    #+#             */
/*   Updated: 2021/05/23 19:48:29 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vec.h"
#include <math.h>

t_vec3	ft_vec_div_f(const double t, const t_vec3 v)
{
	return (ft_vec_mul_f(1 / t, v));
}

double	ft_vec_dot(const t_vec3 u, const t_vec3 v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec3	ft_vec_cross(const t_vec3 u, const t_vec3 v)
{
	t_vec3	result;

	result.x = u.y * v.z - u.z * v.y;
	result.y = u.z * v.x - u.x * v.z;
	result.z = u.x * v.y - u.y * v.x;
	return (result);
}

double	ft_vec_len(const t_vec3 v)
{
	return (sqrt(ft_vec_sqr_len(v)));
}

double	ft_vec_sqr_len(const t_vec3 v)
{
	return (pow(v.x, 2.0) + pow(v.y, 2.0) + pow(v.z, 2.0));
}
