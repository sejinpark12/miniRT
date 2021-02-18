/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:44:13 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/18 14:25:01 by sejpark          ###   ########.fr       */
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
// 21.02.08 sphere.h 에 있던 t_t 구조체를 vec3.h으로 이동. 각각의 도형 코드에 t_t가 있으면 중복 선언이라서
typedef struct	s_t
{
	float		min;
	float		max;
}				t_t;
// sphere.h에 있던 t_coef 구초체를 vec3.h로 이동. 교차점 여부를 구하기 위한 판별식의 계수는 구뿐만 아니라 타원을 구할때도 필요하므로. 각각의 도형 코드에 선언되어 있느면 중복 선언이므로
typedef	struct	s_coef
{
	float		a;
	float		half_b;
	float		c;
}				t_coef;
t_vec3			ft_vec3_add(const t_vec3 u, const t_vec3 v);
t_vec3			ft_vec3_sub(const t_vec3 u, const t_vec3 v);
t_vec3			ft_vec3_mul(const t_vec3 u, const t_vec3 v);
t_vec3			ft_vec3_div(const t_vec3 u, const t_vec3 v);
t_vec3			ft_vec3_mul_f(const float t, const t_vec3 v);
t_vec3			ft_vec3_div_f(const float t, const t_vec3 v);
float			ft_vec3_dot(const t_vec3 u, const t_vec3 v);
t_vec3			ft_vec3_cross(const t_vec3 u, const t_vec3 v);
float			ft_vec3_len(const t_vec3 v);
float			ft_vec3_sqr_len(const t_vec3 v);
t_vec3			ft_vec3_unit_vec(const t_vec3 v);
t_vec3			ft_vec3_set_xyz(const float x, const float y, const float z);
int				create_trgb(const int t, const int r, const int g, const int b);
typedef	t_vec3	t_point3;
typedef	t_vec3	t_color;
#endif
