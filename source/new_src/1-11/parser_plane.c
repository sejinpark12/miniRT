/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:36:27 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/11 11:37:20 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_plane.h"

void	ft_parse_plane(t_engine *engine, char **split_line,
				t_plane_scene_data *ps_data)
{
	char	**split_comma;

	split_comma = ft_get_split_data(engine, split_line[1], ',');
	ps_data->center = ft_vec_set_xyz(ft_atof(split_comma[0], engine),
				ft_atof(split_comma[1], engine), ft_atof(split_comma[2], engine));
	ft_add_split_data_to_par_lst(engine, split_comma);
	split_comma = ft_get_split_data(engine, split_line[2], ',');
	ps_data->norm = ft_vec_set_xyz(ft_atof(split_comma[0], engine),
				ft_atof(split_comma[1], engine), ft_atof(split_comma[2], engine));
	ft_add_split_data_to_par_lst(engine, split_comma);
	split_comma = ft_get_split_data(engine, split_line[3], ',');
	ps_data->color = ft_vec_set_xyz(ft_atoi_minirt(split_comma[0], engine),
						ft_atoi_minirt(split_comma[1], engine),
						ft_atoi_minirt(split_comma[2], engine));
	ft_add_split_data_to_par_lst(engine, split_comma);
	if (ft_chk_dirrange(ps_data->norm) == 0 ||
									ft_chk_colorrange(ps_data->color) == 0)
		error_handler("sphere의 데이터 범위가 잘못되었습니다.", engine);
}

void	ft_alloc_plane(t_engine *engine, char **split_line)
{
	t_objs				objs;
	t_plane_scene_data	ps_data;
	t_obj_lst			*new_obj_lst;

	ft_parse_plane(engine, split_line, &ps_data);
	objs.pl = (t_plane*)malloc(sizeof(t_plane));
	if (objs.pl == NULL)
		error_handler("plane 메모리 동적할당 실패", engine);
	*(objs.pl) = ft_plane_set(ps_data.center, ps_data.norm, ps_data.color);
	new_obj_lst = ft_hit_lst_newobj(objs.pl, 2);
	if (new_obj_lst == NULL)
		error_handler("ft_hit_lst_newobj 메모리 동적할당 실패", engine);
	ft_hit_lst_addback(&engine->obj_lst, new_obj_lst);
}
