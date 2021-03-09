/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 22:50:28 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/09 14:39:45 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H
# include "hittable.h"

typedef struct	s_cylinder_scene_data
{
	t_point3	center;
	t_vec3		dir;
	double		diameter;
	double		h;
	t_color		color;
}				t_cylinder_scene_data;
typedef struct s_cylinder
{
	t_point3	center;
	t_vec3		dir;
	double		radius;
	double		height;
	t_color		color;
	t_point3	top_center;
	t_point3	bottom_center;
}				t_cylinder;
typedef struct s_cylinder_ts
{
	double		cy_t;
	double		cap_t;
}				t_cylinder_ts;
t_cylinder		ft_cylinder_set(t_cylinder_scene_data *cys_data);
double			ft_cylinder_solve_t(t_cylinder *cy, t_ray *r, t_t *t_range);
int				ft_cycap_chk_r(t_ray *r, double t, t_vec3 cap_center,
					double radius);
double			ft_cycap_solve_t(t_cylinder *cy, t_ray *r, t_t *t_range);
void			ft_cylinder_set_rec(t_cylinder *cy, t_ray *r, t_hit_rec *rec,
					t_cylinder_ts cy_ts);
int				ft_cylinder_hit(t_cylinder *cy, t_ray *r, t_t *t_range,
					t_hit_rec *rec);
int				ft_cylinder_sha_hit(t_cylinder *cy, t_ray *r, t_t *t_range);

#endif
