/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 22:50:28 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/19 00:20:21 by sejpark          ###   ########.fr       */
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
	t_point3	top_center;
	t_point3	bottom_center;
}				t_cylinder;
t_cylinder		ft_cylinder_set(t_point3 cen, t_vec3 dir, float diameter,
								float h, t_color color);
float			ft_cylinder_solve_t(t_cylinder *cy, t_ray *r, t_t t_range);
float			ft_cycap_solve_t(t_cylinder *cy, t_ray *r, t_t t_range);
int				ft_cylinder_hit(t_cylinder *cy, t_ray *r, t_t t, t_hit_rec *rec);

#endif
