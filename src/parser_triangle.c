/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_triangle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:56:06 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/13 19:32:08 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_triangle.h"

void	ft_parse_triangle(t_engine *engine, char **split_line,
				t_triangle_scene_data *trs_data)
{
	char	**split_comma;

	split_comma = ft_get_split_data(engine, split_line[1], ',', 3);
	trs_data->p0 = ft_vec_set_xyz(ft_atof(split_comma[0], engine),
									ft_atof(split_comma[1], engine),
									ft_atof(split_comma[2], engine));
	ft_add_split_data_to_par_lst(engine, split_comma);
	split_comma = ft_get_split_data(engine, split_line[2], ',', 3);
	trs_data->p1 = ft_vec_set_xyz(ft_atof(split_comma[0], engine),
									ft_atof(split_comma[1], engine),
									ft_atof(split_comma[2], engine));
	ft_add_split_data_to_par_lst(engine, split_comma);
	split_comma = ft_get_split_data(engine, split_line[3], ',', 3);
	trs_data->p2 = ft_vec_set_xyz(ft_atof(split_comma[0], engine),
									ft_atof(split_comma[1], engine),
									ft_atof(split_comma[2], engine));
	ft_add_split_data_to_par_lst(engine, split_comma);
	split_comma = ft_get_split_data(engine, split_line[4], ',', 3);
	trs_data->color = ft_vec_set_xyz(ft_atoi_minirt(split_comma[0], engine),
									ft_atoi_minirt(split_comma[1], engine),
									ft_atoi_minirt(split_comma[2], engine));
	ft_add_split_data_to_par_lst(engine, split_comma);
	if (ft_chk_colorrange(trs_data->color) == 0)
		error_handler("triangle의 데이터 범위가 잘못되었습니다.", engine);
}

void	ft_alloc_triangle(t_engine *engine, char **split_line)
{
	t_objs					objs;
	t_triangle_scene_data	trs_data;
	t_obj_lst				*new_obj_lst;

	ft_parse_triangle(engine, split_line, &trs_data);
	objs.tr = (t_triangle*)malloc(sizeof(t_triangle));
	if (objs.tr == NULL)
		error_handler("triangle 메모리 동적할당 실패", engine);
	*(objs.tr) = ft_triangle_set(trs_data.p0, trs_data.p1, trs_data.p2,
							trs_data.color);
	new_obj_lst = ft_hit_lst_newobj(objs.tr, 5);
	if (new_obj_lst == NULL)
		error_handler("ft_hit_lst_newobj 메모리 동적할당 실패", engine);
	ft_hit_lst_addback(&engine->obj_lst, new_obj_lst);
}
