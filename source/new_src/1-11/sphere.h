/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:22:40 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/09 16:20:13 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H
# include "hittable.h"

typedef struct	s_sphere_scene_data
{
	t_point3	center;
	double		diameter;
	t_color		color;
}				t_sphere_scene_data;
typedef struct	s_sphere
{
	t_point3	center;
	double		radius;
	t_color		color;
}				t_sphere;
t_sphere		ft_sphere_set(t_point3 cen, double diameter, t_color color);
double			ft_sphere_solve_t(t_sphere *sp, t_ray *r, t_t *t_range);
int				ft_sphere_hit(t_sphere *sp, t_ray *r, t_t *t_range,
					t_hit_rec *rec);
int				ft_sphere_sha_hit(t_sphere *sp, t_ray *r, t_t *t_range);
#endif
