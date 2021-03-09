/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:36:27 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/09 18:57:41 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_plane.h"

int		ft_parse_plane(t_engine *engine, char **split_line)
{
	int						result;
	char					**split_comma;
	t_objs					objs;
	t_plane_scene_data		ps_data;

	result = 1;
	split_comma = ft_split(split_line[1], ',');
	ps_data.center = ft_vec_set_xyz(ft_atof(split_comma[0]),
					ft_atof(split_comma[1]), ft_atof(split_comma[2]));
	ft_free_split(split_comma);
	split_comma = ft_split(split_line[2], ',');
	ps_data.norm = ft_vec_set_xyz(ft_atof(split_comma[0]),
					ft_atof(split_comma[1]), ft_atof(split_comma[2]));
	ft_free_split(split_comma);
	split_comma = ft_split(split_line[3], ',');
	ps_data.color = ft_vec_set_xyz(ft_atoi(split_comma[0]),
					ft_atoi(split_comma[1]), ft_atoi(split_comma[2]));
	ft_free_split(split_comma);
	if (ft_chk_dirrange(ps_data.norm) == 0 ||
									ft_chk_colorrange(ps_data.color) == 0)
		result = 0;
	else
	{
		objs.pl = (t_plane*)malloc(sizeof(t_plane));
		*(objs.pl) = ft_plane_set(ps_data.center, ps_data.norm, ps_data.color);
		ft_hit_lst_addback(&engine->obj_lst, ft_hit_lst_newobj(objs.pl, 2));
	}
	return (result);
}

