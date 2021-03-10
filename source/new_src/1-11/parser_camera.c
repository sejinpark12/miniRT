/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:23:42 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/10 23:11:23 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_camera.h"

void	ft_parse_camera(t_engine *engine, char **split_line,
			t_cam_scene_data *cs_data)
{
	char		**split_comma;
	t_par_lst	*new_par_lst;

	split_comma = ft_split(split_line[1], ',');
	if (split_comma == NULL)
		error_handler("ft_split 함수 메모리 동적할당 실패", engine);
	cs_data->viewpoint = ft_vec_set_xyz(ft_atof(split_comma[0], engine),
		ft_atof(split_comma[1], engine), ft_atof(split_comma[2], engine));
	new_par_lst = ft_par_lst_new(split_comma);
	if (new_par_lst == NULL)
		error_handler("ft_par_lst_new 함수 메모리 동적할당 실패", engine);
	ft_par_lst_addback(&engine->parser_lst, new_par_lst);
	split_comma = ft_split(split_line[2], ',');
	if (split_comma == NULL)
		error_handler("ft_split 함수 메모리 동적할당 실패", engine);
	cs_data->dir = ft_vec_set_xyz(ft_atof(split_comma[0], engine),
		ft_atof(split_comma[1], engine), ft_atof(split_comma[2], engine));
	new_par_lst = ft_par_lst_new(split_comma);
	if (new_par_lst == NULL)
		error_handler("ft_par_lst_new 함수 메모리 동적할당 실패", engine);
	ft_par_lst_addback(&engine->parser_lst, new_par_lst);
	cs_data->fov = ft_atoi_minirt(split_line[3], engine);
	if (ft_chk_dirrange(cs_data->dir) == 0 || ft_chk_fovrange(cs_data->fov)
			== 0)
		error_handler("camera의 데이터 범위가 잘못 되었습니다."	, engine);
}

void	ft_alloc_camera(t_engine *engine, char **split_line)
{
	t_cams				cams;
	t_cam_scene_data	cs_data;
	t_obj_lst			*new_obj_lst;

	ft_parse_camera(engine, split_line, &cs_data);
	cams.cam = (t_camera*)malloc(sizeof(t_camera));
	if (cams.cam == NULL)
		error_handler("camera 메모리 동적할당 실패", engine);
	*(cams.cam) = ft_camera_set(cs_data.viewpoint, cs_data.dir,
					cs_data.fov);
	new_obj_lst = ft_hit_lst_newobj(cams.cam, 20);
	if (new_obj_lst == NULL)
		error_handler("ft_hit_lst_newobj 메모리 동적할당 실패", engine);
	ft_hit_lst_addback(&engine->cam_lst, new_obj_lst);
}
