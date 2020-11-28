/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:46:04 by sejpark           #+#    #+#             */
/*   Updated: 2020/11/24 12:56:14 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

float	ft_vec3_get_x(const t_vec3 *vec3)
{
	return (vec3->e[0]);
}

float	ft_vec3_get_y(const t_vec3 *vec3)
{
	return (vec3->e[1]);
}

float	ft_vec3_get_z(const t_vec3 *vec3)
{
	return (vec3->e[2]);
}

float	ft_vec3_length(const t_vec3 *vec3)
{
	return (sqrt(ft_vec3_length_squared(vec3)));
}

float	ft_vec3_length_squared(const t_vec3 *vec3)
{
	float result;

	result = pow(vec3->e[0], 2.0) + pow(vec3->e[1], 2.0) + pow(vec3->e[2], 2.0);
	return (result);
}

t_vec3	*ft_vec3_add(t_vec3 *target, const t_vec3 *u, const t_vec3 *v)
{
	target->e[0] = u->e[0] + v->e[0];
	target->e[1] = u->e[1] + v->e[1];
	target->e[2] = u->e[2] + v->e[2];
	return (target);
}

t_vec3	*ft_vec3_subtract(t_vec3 *target, const t_vec3 *u, const t_vec3 *v)
{
	target->e[0] = u->e[0] - v->e[0];
	target->e[1] = u->e[1] - v->e[1];
	target->e[2] = u->e[2] - v->e[2];
	return (target);
}

t_vec3	*ft_vec3_multiply(t_vec3 *target, const t_vec3 *u, const t_vec3 *v)
{
	target->e[0] = u->e[0] * v->e[0];
	target->e[1] = u->e[1] * v->e[1];
	target->e[2] = u->e[2] * v->e[2];
	return (target);
}

t_vec3	*ft_vec3_divide(t_vec3 *target, const t_vec3 *u, const t_vec3 *v)
{
	target->e[0] = u->e[0] / v->e[0];
	target->e[1] = u->e[1] / v->e[1];
	target->e[2] = u->e[2] / v->e[2];
	return (target);
}

t_vec3	*ft_vec3_multiply_float(t_vec3 *target, const float t, const t_vec3 *v)
{
	target->e[0] = v->e[0] * t;
	target->e[1] = v->e[1] * t;
	target->e[2] = v->e[2] * t;
	return (target);
}

t_vec3	*ft_vec3_divide_float(t_vec3 *target, const float t, const t_vec3 *v)
{
	ft_vec3_multiply_float(target, (1 / t), v);
	return (target);
}

float	ft_vec3_dot(const t_vec3 *u, const t_vec3 *v)
{
	return (u->e[0] * v->e[0] + u->e[1] * v->e[1] + u->e[2] * v->e[2]);
}

t_vec3	*ft_vec3_cross(t_vec3 *target, const t_vec3 *u, const t_vec3 *v)
{
	target->e[0] = u->e[1] * v->e[2] - u->e[2] * v->e[1];
	target->e[1] = u->e[2] * v->e[0] - u->e[0] * v->e[2];
	target->e[2] = u->e[0] * v->e[1] - u->e[1] * v->e[0];
	return (target);
}

t_vec3	*ft_unit_vector(t_vec3 *target, const t_vec3 *v)
{
	ft_vec3_divide_float(target, ft_vec3_length(v), v);
	return (target);
}

void	ft_vec3_set_rgb(t_vec3 *vec, float r, float g, float b)
{
	vec->e[0] = r;
	vec->e[1] = g;
	vec->e[2] = b;
}

void	ft_vec3_set_vec(t_vec3 *vec, const t_vec3 *v)
{
	vec->e[0] = v->e[0];
	vec->e[1] = v->e[1];
	vec->e[2] = v->e[2];
}

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

//static t_vec3	random(float min, float max)
//{
//	return ()
//}
