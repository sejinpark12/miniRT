/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:23:42 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/09 18:56:56 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_camera.h"

int		ft_parse_camera(t_engine *engine, char **split_line)
{
	int					result;
	char				**split_comma;
	t_cams				cams;
	t_cam_scene_data	cs_data;

	result = 1;
	split_comma = ft_split(split_line[1], ',');
	cs_data.viewpoint = ft_vec_set_xyz(ft_atof(split_comma[0]),
						ft_atof(split_comma[1]), ft_atof(split_comma[2]));
	ft_free_split(split_comma);
	split_comma = ft_split(split_line[2], ',');
	cs_data.dir = ft_vec_set_xyz(ft_atof(split_comma[0]),
							ft_atof(split_comma[1]), ft_atof(split_comma[2]));
	ft_free_split(split_comma);
	cs_data.fov = ft_atoi(split_line[3]);
	if (ft_chk_dirrange(cs_data.dir) == 0 || ft_chk_fovrange(cs_data.fov) == 0)
		result = 0;
	else
	{
		cams.cam = (t_camera*)malloc(sizeof(t_camera));
		*(cams.cam) = ft_camera_set(cs_data.viewpoint, cs_data.dir, cs_data.fov);
		ft_hit_lst_addback(&engine->cam_lst, ft_hit_lst_newobj(cams.cam, 20));
	}
	return (result);
}
