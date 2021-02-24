/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 22:50:28 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/24 17:29:57 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H
# include "hittable.h"
# include "vec3.h"

typedef struct		s_cy_info
{
	t_point3		center;
	t_vec3			dir;
	// 그림자 여드름 현상 최소화하기 위해서 타입을 엔진의 모든 타입을 
	// float에서 double로 바꿈
	double			radius;  
	double			height;
	t_color			color;
}					t_cy_info;
typedef	struct		s_cycap_info
{
	t_point3		top_center;
	t_point3		bottom_center;
}					t_cycap_info;
typedef struct		s_cylinder
{
	t_cy_info		cy_info;
	t_cycap_info	cycap_info;
}					t_cylinder;
//t_cylinder			ft_cylinder_set(t_point3 cen, t_vec3 dir, float diameter, float h, t_color color);
t_cylinder			ft_cylinder_set(const t_cyclinder *cy);
float				ft_cylinder_solve_t(t_cylinder *cy, t_ray *r, t_t t_range);
float				ft_cycap_solve_t(t_cylinder *cy, t_ray *r, t_t t_range);
int					ft_cylinder_hit(t_cylinder *cy, t_ray *r, t_t t,
						t_hit_rec *rec);

#endif
