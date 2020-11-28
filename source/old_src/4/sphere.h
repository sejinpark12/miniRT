/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 11:11:48 by sejpark           #+#    #+#             */
/*   Updated: 2020/11/21 13:26:51 by sejpark          ###   ########.fr       */
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
void			ft_sphere_set(
							t_sphere		*sp,
							const t_point3	*cen,
							const float		r);
int				ft_sphere_hit(
							t_sphere		*sp,
							const t_ray		*r,
							float			t_min,
							float			t_max,
							t_hit_rec		*rec);
#endif
