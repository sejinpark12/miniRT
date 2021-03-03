/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 20:36:59 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/01 20:01:17 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SQUARE_H
# define SQUARE_H
# include "hittable.h"
# include "plane.h"

typedef struct	s_square
{
	t_plane		sq_plane;
	float		side_size;
	t_vec3		floor;
	t_vec3		half_size;
	t_vec3		center_to_ip;
}				t_square;
t_square		ft_square_set(t_point3 cen, t_vec3 norm, float side_size,
									t_color color);
float			ft_square_solve_t(t_square *sq, t_ray *r, t_t *t_range);
int				ft_square_chk_size(t_square *sq, t_ray *r, float t);
int				ft_square_hit(t_square *sq, t_ray *r, t_t *t_range,
									t_hit_rec *rec);
int				ft_square_sha_hit(t_square *sq, t_ray *r, t_t *t_range);
#endif
