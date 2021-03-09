/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_triangle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:56:06 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/09 18:58:18 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_triangle.h"

int		ft_parse_triangle(t_engine *engine, char **split_line)
{
	int						result;
	char					**split_comma;
	t_objs					objs;
	t_triangle_scene_data	trs_data;

	result = 1;
	split_comma = ft_split(split_line[1], ',');
	trs_data.p0 = ft_vec_set_xyz(ft_atof(split_comma[0]),
					ft_atof(split_comma[1]), ft_atof(split_comma[2]));
	ft_free_split(split_comma);
	split_comma = ft_split(split_line[2], ',');
	trs_data.p1 = ft_vec_set_xyz(ft_atof(split_comma[0]),
					ft_atof(split_comma[1]), ft_atof(split_comma[2]));
	ft_free_split(split_comma);
	split_comma = ft_split(split_line[3], ',');
	trs_data.p2 = ft_vec_set_xyz(ft_atof(split_comma[0]),
					ft_atof(split_comma[1]), ft_atof(split_comma[2]));
	ft_free_split(split_comma);
	split_comma = ft_split(split_line[4], ',');
	trs_data.color = ft_vec_set_xyz(ft_atoi(split_comma[0]),
					ft_atoi(split_comma[1]), ft_atoi(split_comma[2]));
	ft_free_split(split_comma);
	if (ft_chk_colorrange(trs_data.color) == 0)
		result = 0;
	else
	{
		objs.tr = (t_triangle*)malloc(sizeof(t_triangle));
		*(objs.tr) = ft_triangle_set(trs_data.p0, trs_data.p1, trs_data.p2,
								trs_data.color);
		ft_hit_lst_addback(&engine->obj_lst, ft_hit_lst_newobj(objs.tr, 5));
	}
	return (result);
}
