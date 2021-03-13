/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:32:36 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/13 19:31:18 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_sphere.h"

void	ft_parse_sphere(t_engine *engine, char **split_line,
			t_sphere_scene_data *sps_data)
{
	char	**split_comma;

	split_comma = ft_get_split_data(engine, split_line[1], ',', 3);
	sps_data->center = ft_vec_set_xyz(ft_atof(split_comma[0], engine),
									ft_atof(split_comma[1], engine),
									ft_atof(split_comma[2], engine));
	ft_add_split_data_to_par_lst(engine, split_comma);
	sps_data->diameter = ft_atof(split_line[2], engine);
	split_comma = ft_get_split_data(engine, split_line[3], ',', 3);
	sps_data->color = ft_vec_set_xyz(ft_atoi_minirt(split_comma[0], engine),
									ft_atoi_minirt(split_comma[1], engine),
									ft_atoi_minirt(split_comma[2], engine));
	ft_add_split_data_to_par_lst(engine, split_comma);
	if (ft_chk_colorrange(sps_data->color) == 0)
		error_handler("sphere의 데이터 범위가 잘못되었습니다.", engine);
}

void	ft_alloc_sphere(t_engine *engine, char **split_line)
{
	t_objs					objs;
	t_sphere_scene_data		sps_data;
	t_obj_lst				*new_obj_lst;

	ft_parse_sphere(engine, split_line, &sps_data);
	objs.sp = (t_sphere*)malloc(sizeof(t_sphere));
	if (objs.sp == NULL)
		error_handler("sphere 메모리 동적할당 실패", engine);
	*(objs.sp) = ft_sphere_set(sps_data.center, sps_data.diameter,
									sps_data.color);
	new_obj_lst = ft_hit_lst_newobj(objs.sp, 1);
	if (new_obj_lst == NULL)
		error_handler("ft_hit_lst_newobj 메모리 동적할당 실패", engine);
	ft_hit_lst_addback(&engine->obj_lst, new_obj_lst);
}
