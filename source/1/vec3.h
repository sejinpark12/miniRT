/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:00:59 by sejpark           #+#    #+#             */
/*   Updated: 2020/11/26 15:28:22 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H
# include <math.h>
# include <stdlib.h>

typedef	struct	s_vec3
{
	float		e[3];
}				t_vec3;
float			ft_vec3_get_x(const t_vec3 *vec3);
float			ft_vec3_get_y(const t_vec3 *vec3);
float			ft_vec3_get_z(const t_vec3 *vec3);
float			ft_vec3_length(const t_vec3 *vec3);
float			ft_vec3_length_squared(const t_vec3 *vec3);
void			ft_vec3_add(t_vec3 *target, const t_vec3 *u, const t_vec3 *v);
//t_vec3			*ft_vec3_add(const t_vec3 *u, const t_vec3 *v);
void			ft_vec3_subtract(t_vec3 *target, const t_vec3 *u, const t_vec3 *v);
//t_vec3			*ft_vec3_subtract(const t_vec3 *u, const t_vec3 *v);
void			ft_vec3_multiply(t_vec3 *target, const t_vec3 *u, const t_vec3 *v);
//t_vec3			*ft_vec3_multiply(const t_vec3 *u, const t_vec3 *v);
void			ft_vec3_divide(t_vec3 *target, const t_vec3 *u, const t_vec3 *v);
//t_vec3			*ft_vec3_divide(const t_vec3 *u, const t_vec3 *v);
void			ft_vec3_multiply_float(t_vec3 *target, const float t, const t_vec3 *v);
//t_vec3			*ft_vec3_multiply_float(const float t, const t_vec3 *v);
void			ft_vec3_divide_float(t_vec3 *target, const float t, const t_vec3 *v);
//t_vec3			*ft_vec3_divide_float(const float t, const t_vec3 *v);
float			ft_dot(const t_vec3 *u, const t_vec3 *v);
void			ft_cross(t_vec3 *target, const t_vec3 *u, const t_vec3 *v);
//t_vec3			*ft_cross(const t_vec3 *u, const t_vec3 *v);
void			ft_unit_vector(t_vec3 *target, const t_vec3 *v);
//t_vec3			*ft_unit_vector(const t_vec3 *v);
int				create_trgb(int t, int r, int g, int b);
void			ft_vec3_set_rgb(t_vec3 *vec, float r, float g, float b);
void			ft_vec3_set_vec(t_vec3 *vec, const t_vec3 *v);
#endif
