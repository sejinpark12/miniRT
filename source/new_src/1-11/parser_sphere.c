/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:32:36 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/09 18:58:00 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_sphere.h"

int		ft_parse_sphere(t_engine *engine, char **split_line)
{
	int						result;
	char					**split_comma;
	t_objs					objs;
	t_sphere_scene_data		sps_data;

	result = 1;
	split_comma = ft_split(split_line[1], ',');
	sps_data.center = ft_vec_set_xyz(ft_atof(split_comma[0]),
						ft_atof(split_comma[1]), ft_atof(split_comma[2]));
	ft_free_split(split_comma);
	sps_data.diameter = ft_atof(split_line[2]);
	split_comma = ft_split(split_line[3], ',');
	sps_data.color = ft_vec_set_xyz(ft_atoi(split_comma[0]),
						ft_atoi(split_comma[1]), ft_atoi(split_comma[2]));
	ft_free_split(split_comma);
	if (ft_chk_colorrange(sps_data.color) == 0)
		result = 0;
	else
	{
		objs.sp = (t_sphere*)malloc(sizeof(t_sphere));
		*(objs.sp) = ft_sphere_set(sps_data.center, sps_data.diameter,
										sps_data.color);
		ft_hit_lst_addback(&engine->obj_lst, ft_hit_lst_newobj(objs.sp, 1));
	}
	return (result);
}
