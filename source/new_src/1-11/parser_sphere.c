/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:32:36 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/10 23:26:51 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_sphere.h"

void	ft_parse_sphere(t_engine *engine, char **split_line,
			t_sphere_scene_data *sps_data)
{
	char		**s_c;
	t_par_lst	*new_par_lst;

	s_c = ft_split(split_line[1], ',');
	if (s_c == NULL)
		error_handler("ft_split 함수 메모리 동적할당 실패", engine);
	sps_data->center = ft_vec_set_xyz(ft_atof(s_c[0], engine),
		ft_atof(s_c[1], engine), ft_atof(s_c[2], engine));
	new_par_lst = ft_par_lst_new(s_c);
	if (new_par_lst == NULL)
		error_handler("ft_par_lst_new 함수 메모리 동적할당 실패", engine);
	ft_par_lst_addback(&engine->parser_lst, new_par_lst);
	sps_data->diameter = ft_atof(split_line[2], engine);
	s_c = ft_split(split_line[3], ',');
	if (s_c == NULL)
		error_handler("ft_split 함수 메모리 동적할당 실패", engine);
	sps_data->color = ft_vec_set_xyz(ft_atoi_minirt(s_c[0], engine),
			ft_atoi_minirt(s_c[1], engine), ft_atoi_minirt(s_c[2], engine));
	new_par_lst = ft_par_lst_new(s_c);
	if (new_par_lst == NULL)
		error_handler("ft_par_lst_new 함수 메모리 동적할당 실패", engine);
	ft_par_lst_addback(&engine->parser_lst, new_par_lst);
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
