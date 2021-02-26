/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 23:58:12 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/23 21:56:12 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H
# include "vec3.h"
# include <math.h>

typedef struct	s_splight
{
	t_point3	pos;
	float		intensity;
	t_color		color;
}				t_splight;
typedef struct	s_spli_info
{
	t_vec3		lightdir;
	t_color		lightintensity;
	float		distance;
}				t_spli_info;
typedef struct	s_dilight
{
	t_point3	pos;
	t_vec3		dir;
	float		intensity;
	t_color		color;
}				t_dilight;
t_splight		ft_splight_set(t_point3 pos, float intensity, t_color color);
t_spli_info		ft_splight_get_info(t_splight *spli, t_point3 *p);
t_dilight		ft_dilight_set(t_point3 pos, t_vec3 dir, float intensity,
															t_color color);
#endif
