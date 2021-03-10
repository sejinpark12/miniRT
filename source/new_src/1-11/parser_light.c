/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:28:34 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/10 23:11:15 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_light.h"

void	ft_parse_light(t_engine *engine, char **split_line,
			t_light_scene_data *ls_data)
{
	char		**s_c;
	t_par_lst	*new_par_lst;

	s_c = ft_split(split_line[1], ',');
	if (s_c == NULL)
		error_handler("ft_split 함수 메모리 동적할당 실패", engine);
	ls_data->pos = ft_vec_set_xyz(ft_atof(s_c[0], engine),
		ft_atof(s_c[1], engine), ft_atof(s_c[2], engine));
	new_par_lst = ft_par_lst_new(s_c);
	if (new_par_lst == NULL)
		error_handler("ft_par_lst_new 함수 메모리 동적할당 실패", engine);
	ft_par_lst_addback(&engine->parser_lst, new_par_lst);
	ls_data->intensity = ft_atof(split_line[2], engine);
	s_c = ft_split(split_line[3], ',');
	if (s_c == NULL)
		error_handler("ft_split 함수 메모리 동적할당 실패", engine);
	ls_data->color = ft_vec_set_xyz(ft_atoi_minirt(s_c[0], engine),
			ft_atoi_minirt(s_c[1], engine), ft_atoi_minirt(s_c[2], engine));
	new_par_lst = ft_par_lst_new(s_c);
	if (new_par_lst == NULL)
		error_handler("ft_par_lst_new 함수 메모리 동적할당 실패", engine);
	ft_par_lst_addback(&engine->parser_lst, new_par_lst);
	if (ft_chk_lightrange(ls_data->intensity) == 0 ||
							ft_chk_colorrange(ls_data->color) == 0)
		error_handler("light의 데이터 범위가 잚못되었습니다.", engine);
}

void	ft_alloc_light(t_engine *engine, char **split_line)
{
	t_lights			lights;
	t_light_scene_data	ls_data;
	t_obj_lst			*new_obj_lst;

	ft_parse_light(engine, split_line, &ls_data);
	lights.spli = (t_splight*)malloc(sizeof(t_splight));
	if (lights.spli == NULL)
		error_handler("light 메모리 동적할당 실패", engine);
	*(lights.spli) = ft_splight_set(ls_data.pos, ls_data.intensity,
									ls_data.color);
	new_obj_lst = ft_hit_lst_newobj(lights.spli, 10);
	if (new_obj_lst == NULL)
		error_handler("ft_hit_lst_newobj 메모리 동적할당 실패", engine);
	ft_hit_lst_addback(&engine->light_lst, new_obj_lst);
}
