/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 20:36:59 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/17 22:10:06 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SQUARE_H
# define SQUARE_H
# include "hittable.h"
# include "vec3.h"

typedef struct	s_square
{
	t_point3	center;
	t_vec3		norm;
	t_color		color;
	float		side_size;
	t_vec3		floor;
	t_vec3		half_size;
	t_vec3		center_to_ip;
}				t_square;
t_square		ft_square_set(t_point3 cen, t_vec3 norm, float side_size, t_color color);
float			ft_square_solve_t(t_square *sq, t_ray *r);
int				ft_square_hit(t_square *sq, t_ray *r, t_t t_range, t_hit_rec *rec);
#endif
