/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:48:09 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/10 15:10:40 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "math.h"

t_vec3	ft_vec3_add(const t_vec3 u, const t_vec3 v)
{
//	t_vec3 result;
//
//	result.x = u->x + v->x;
//	result.y = u->y + v->y;
//	result.z = u->z + v->z;
//	return (result);
	return ((t_vec3){u.x + v.x, u.y + v.y, u.z + v.z});
}

t_vec3	ft_vec3_sub(const t_vec3 u, const t_vec3 v)
{
//	t_vec3 result;
//
//	result.x = u->x - v->x;
//	result.y = u->y - v->y;
//	result.z = u->z - v->z;
//	return (result);
	return ((t_vec3){u.x - v.x, u.y - v.y, u.z - v.z});
}

t_vec3	ft_vec3_mul(const t_vec3 u, const t_vec3 v)
{
//	t_vec3 result;
//
//	result.x = u.x * v.x;
//	result.y = u.y * v.y;
//	result.z = u.z * v.z;
//	return (result);
	return ((t_vec3){u.x * v.x, u.y * v.y, u.z * v.z});
}

t_vec3	ft_vec3_div(const t_vec3 u, const t_vec3 v)
{
//	t_vec3 result;
//
//	result.x = u.x / v.x;
//	result.y = u.y / v.y;
//	result.z = u.z / v.z;
//	return (result);
	return ((t_vec3){u.x / v.x, u.y / v.y, u.z / v.z});
}

t_vec3	ft_vec3_mul_f(const float t, const t_vec3 v)
{
//	t_vec3 result;
//
//	result.x = v.x * t;
//	result.y = v.y * t;
//	result.z = v.z * t;
//	return (result);
	return ((t_vec3){v.x * t, v.y * t, v.z * t});
}

t_vec3	ft_vec3_div_f(const float t, const t_vec3 v)
{
	return (ft_vec3_mul_f(1 / t, v));
}

float	ft_vec3_dot(const t_vec3 u, const t_vec3 v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec3	ft_vec3_cross(const t_vec3 u, const t_vec3 v)
{
	t_vec3 result;

	result.x = u.y * v.z - u.z * v.y;
	result.y = u.z * v.x - u.x * v.z;
	result.z = u.x * v.y - u.y * v.x;
	return (result);
}

float	ft_vec3_len(const t_vec3 v)
{
	return (sqrt(ft_vec3_sqr_len(v)));
}

float	ft_vec3_sqr_len(const t_vec3 v)
{
	return (pow(v.x, 2.0) + pow(v.y, 2.0) + pow(v.z, 2.0));
}

t_vec3	ft_vec3_unit_vec(const t_vec3 v)
{
	return (ft_vec3_div_f(ft_vec3_len(v), v));
}

t_vec3	ft_vec3_set_xyz(const float x, const float y, const float z)
{
//	t_vec3 result;
//
//	result.x = x;
//	result.y = y;
//	result.z = z;
//	return (result);
	return ((t_vec3){x, y, z});
}

int		create_trgb(const int t, const int r, const int g, const int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
