/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 22:50:28 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/10 22:55:36 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H
# include "hittable.h"
# include "vec3.h"

typedef struct	s_cylinder
{
	t_point3	center;
	t_vec3		dir;
	float		radius;
	float		height;
	t_color		color;
}				t_cylinder;
t_cylinder		ft_cylinder_set(t_point3 cen, t_vec3 dir, float r, float h,
								t_color color);
int				ft_cylinder_hit(t_cylinder *cy, t_ray *r, t_t t, t_hit_rec *rec);

#endif
