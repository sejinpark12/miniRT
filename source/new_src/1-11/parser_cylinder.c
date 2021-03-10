/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:51:59 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/10 10:48:51 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_cylinder.h"

int		ft_parse_cylinder(t_engine *engine, char **split_line)
{
	int						result;
	char					**split_comma;
	t_objs					objs;
	t_cylinder_scene_data	cys_data;

	result = 1;
	split_comma = ft_split(split_line[1], ',');
	cys_data.center = ft_vec_set_xyz(ft_atof(split_comma[0], engine),
					ft_atof(split_comma[1], engine), ft_atof(split_comma[2], engine));
	ft_free_split(split_comma);
	split_comma = ft_split(split_line[2], ',');
	cys_data.dir = ft_vec_set_xyz(ft_atof(split_comma[0], engine),
					ft_atof(split_comma[1], engine), ft_atof(split_comma[2], engine));
	ft_free_split(split_comma);
	cys_data.diameter = ft_atof(split_line[3], engine);
	cys_data.h = ft_atof(split_line[4], engine);
	split_comma = ft_split(split_line[5], ',');
	cys_data.color = ft_vec_set_xyz(ft_atoi(split_comma[0]),
					ft_atoi(split_comma[1]), ft_atoi(split_comma[2]));
	ft_free_split(split_comma);
	if (ft_chk_dirrange(cys_data.dir) == 0 ||
								ft_chk_colorrange(cys_data.color) == 0)
		result = 0;
	else
	{
		objs.cy = (t_cylinder*)malloc(sizeof(t_cylinder));
		*(objs.cy) = ft_cylinder_set(&cys_data);
		ft_hit_lst_addback(&engine->obj_lst, ft_hit_lst_newobj(objs.cy, 4));
	}
	return (result);
}
