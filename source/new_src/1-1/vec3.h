/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:44:13 by sejpark           #+#    #+#             */
/*   Updated: 2020/11/26 17:17:20 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

typedef struct	s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;
t_vec3			*ft_vec3_add(t_vec3 *target, t_vec3 *u, t_vec3 *v);
t_vec3			*ft_vec3_sub(t_vec3 *target, t_vec3 *u, t_vec3 *v);
t_vec3			*ft_vec3_multi(t_vec3 *target, t_vec3 *u, t_vec3 *v);
t_vec3			*ft_vec3_div(t_vec3 *target, t_vec3 *u, t_vec3 *v);
t_vec3			*ft_vec3_multi_float(t_vec3 *target, float t, t_vec3 *v);
t_vec3			*ft_vec3_div_float(t_vec3 *target, float t, t_vec3 *v);
float			ft_vec3_dot(t_vec3 *u, t_vec3 *v);
t_vec3			*ft_vec3_cross(t_vec3 *target, t_vec3 *u, t_vec3 *v);
float			ft_vec3_len(t_vec3 *target);
float			ft_vec3_len_sqr(t_vec3 *target);
t_vec3			*ft_vec3_unit_vec(t_vec3 *target, t_vec3 *v);
t_vec3			*ft_vec3_set_xyz(t_vec3 *target, float x, float y, float z);
int				create_trgb(int t, int r, int g, int b);
#endif
