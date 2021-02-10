/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:22:40 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/09 20:27:40 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H
# include "hittable.h"
# include "vec3.h"

typedef struct	s_sphere
{
	t_point3	center;
	float		radius;
}				t_sphere;
typedef	struct	s_coef
{
	float		a;
	float		half_b;
	float		c;
}				t_coef;
t_sphere		ft_sphere_set(t_point3 cen, float r);
int				ft_sphere_hit(t_sphere *sp, t_ray *r, t_t t, t_hit_rec *rec);

#endif
