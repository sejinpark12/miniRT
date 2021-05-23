/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:32:51 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/09 16:22:38 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_H
# define TRIANGLE_H
# include "hittable.h"
# include "plane.h"

typedef struct	s_triangle_scene_data
{
	t_point3	p0;
	t_point3	p1;
	t_point3	p2;
	t_color		color;
}				t_triangle_scene_data;
typedef struct	s_tr_pos
{
	t_point3	p0;
	t_point3	p1;
	t_point3	p2;
}				t_tr_pos;
typedef struct	s_edge
{
	t_vec3		edge0;
	t_vec3		edge1;
	t_vec3		edge2;
}				t_edge;
typedef struct	s_c
{
	t_vec3		c0;
	t_vec3		c1;
	t_vec3		c2;
}				t_c;
typedef struct	s_triangle
{
	t_plane		tr_plane;
	t_tr_pos	pos;
	t_edge		edge;
	t_c			c;
}				t_triangle;
t_triangle		ft_triangle_set(t_point3 p0, t_point3 p1, t_point3 p2,
					t_color color);
void			ft_triangle_set_c(t_triangle *tr, t_point3 p);
double			ft_triangle_solve_t(t_triangle *tr, t_ray *r, t_t *t_range);
int				ft_triangle_hit(t_triangle *tr, t_ray *r, t_t *t_range,
					t_hit_rec *rec);
int				ft_triangle_sha_hit(t_triangle *tr, t_ray *r, t_t *t_range);
#endif
