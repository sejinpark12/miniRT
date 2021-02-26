/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:22:40 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/23 10:27:01 by sejpark          ###   ########.fr       */
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
	t_color		color;
}				t_sphere;
t_sphere		ft_sphere_set(t_point3 cen, float diameter, t_color color);
int				ft_sphere_hit(t_sphere *sp, t_ray *r, t_t t_range,
									t_hit_rec *rec);

#endif