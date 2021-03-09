/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:44:13 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/09 15:08:19 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

typedef struct s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;
typedef struct s_t
{
	double		min;
	double		max;
}				t_t;
typedef struct s_coef
{
	double		a;
	double		half_b;
	double		c;
}				t_coef;
t_vec3			ft_vec_add(const t_vec3 u, const t_vec3 v);
t_vec3			ft_vec_sub(const t_vec3 u, const t_vec3 v);
t_vec3			ft_vec_mul(const t_vec3 u, const t_vec3 v);
t_vec3			ft_vec_div(const t_vec3 u, const t_vec3 v);
t_vec3			ft_vec_mul_f(const double t, const t_vec3 v);
t_vec3			ft_vec_div_f(const double t, const t_vec3 v);
double			ft_vec_dot(const t_vec3 u, const t_vec3 v);
t_vec3			ft_vec_cross(const t_vec3 u, const t_vec3 v);
double			ft_vec_len(const t_vec3 v);
double			ft_vec_sqr_len(const t_vec3 v);
t_vec3			ft_vec_unit_vec(const t_vec3 v);
t_vec3			ft_vec_set_xyz(const double x, const double y, const double z);
int				create_trgb(const int t, const int r, const int g, const int b);
typedef t_vec3	t_point3;
typedef t_vec3	t_color;
#endif
