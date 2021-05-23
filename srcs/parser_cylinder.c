/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:51:59 by sejpark           #+#    #+#             */
/*   Updated: 2021/05/23 19:48:29 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser_cylinder.h"

void	ft_parse_cylinder(t_engine *engine, char **split_line,
				t_cylinder_scene_data *cys_data)
{
	char	**split_comma;

	split_comma = ft_get_split_data(engine, split_line[1], ',', 3);
	cys_data->center = ft_vec_set_xyz(ft_atof(split_comma[0], engine),
									ft_atof(split_comma[1], engine),
									ft_atof(split_comma[2], engine));
	ft_add_split_data_to_par_lst(engine, split_comma);
	split_comma = ft_get_split_data(engine, split_line[2], ',', 3);
	cys_data->dir = ft_vec_set_xyz(ft_atof(split_comma[0], engine),
									ft_atof(split_comma[1], engine),
									ft_atof(split_comma[2], engine));
	ft_add_split_data_to_par_lst(engine, split_comma);
	cys_data->diameter = ft_atof(split_line[3], engine);
	cys_data->h = ft_atof(split_line[4], engine);
	split_comma = ft_get_split_data(engine, split_line[5], ',', 3);
	cys_data->color = ft_vec_set_xyz(ft_atoi_minirt(split_comma[0], engine),
									ft_atoi_minirt(split_comma[1], engine),
									ft_atoi_minirt(split_comma[2], engine));
	ft_add_split_data_to_par_lst(engine, split_comma);
	if (ft_chk_dirrange(cys_data->dir) == 0 ||
								ft_chk_colorrange(cys_data->color) == 0)
		error_handler("cylinder의 데이터 범위가 잘못되었습니다.", engine);
}

void	ft_alloc_cylinder(t_engine *engine, char **split_line)
{
	t_objs					objs;
	t_cylinder_scene_data	cys_data;
	t_obj_lst				*new_obj_lst;

	ft_parse_cylinder(engine, split_line, &cys_data);
	objs.cy = (t_cylinder*)malloc(sizeof(t_cylinder));
	if (objs.cy == NULL)
		error_handler("cylinder 메모리 동적할당 실패", engine);
	*(objs.cy) = ft_cylinder_set(&cys_data);
	new_obj_lst = ft_hit_lst_newobj(objs.cy, 4);
	if (new_obj_lst == NULL)
		error_handler("ft_hit_lst_newobj 메모리 동적할당 실패", engine);
	ft_hit_lst_addback(&engine->obj_lst, new_obj_lst);
}
