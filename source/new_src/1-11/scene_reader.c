/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:47:54 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/08 01:38:33 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_reader.h"
#include <fcntl.h>
#include <unistd.h>

void ft_line_parser(t_engine *engine, char *line)
{
	int						i;
	char					**split_line;
	char					**split_comma;
	t_cams					cams;
	t_cam_scene_data		cs_data;
	t_lights				lights;
	t_light_scene_data		ls_data;
	t_objs					objs;
	t_sphere_scene_data		ss_data;
	t_plane_scene_data		ps_data;
	t_cylinder_scene_data	cys_data;
	t_triangle_scene_data	trs_data;

	i = 0;
	split_line = ft_split(line, ' ');
	if (split_line[0][0] == 'R')
	{
		engine->data.width = ft_atoi(split_line[1]);
		engine->data.height = ft_atoi(split_line[2]);
	}
	else if (split_line[0][0] == 'A')
	{
		engine->data.ambient.intensity = ft_atof(split_line[1]);
		split_comma = ft_split(split_line[2], ',');
		engine->data.ambient.color.x = ft_atoi(split_comma[0]);
		engine->data.ambient.color.y = ft_atoi(split_comma[1]);
		engine->data.ambient.color.z = ft_atoi(split_comma[2]);
		while (split_comma[i])
			free(split_comma[i++]);
		free(split_comma);
	}
	else if (split_line[0][0] == 'c')
	{
		split_comma = ft_split(split_line[1], ',');
		cs_data.viewpoint = ft_vec_set_xyz(ft_atof(split_comma[0]),
											ft_atof(split_comma[1]),
											ft_atof(split_comma[2]));
		while (split_comma[i])
			free(split_comma[i++]);
		free(split_comma);
		i = 0;
		split_comma = ft_split(split_line[2], ',');
		cs_data.dir = ft_vec_set_xyz(ft_atof(split_comma[0]),
										ft_atof(split_comma[1]),
										ft_atof(split_comma[2]));
		while (split_comma[i])
			free(split_comma[i++]);
		free(split_comma);
		cams.cam = (t_camera*)malloc(sizeof(t_camera));
		*(cams.cam) = ft_camera_set(cs_data.viewpoint, cs_data.dir,
										ft_atoi(split_line[3]));
		ft_hit_lst_addback(&engine->cam_lst, ft_hit_lst_newobj(cams.cam, 20));
	}
	else if (split_line[0][0] == 'l')
	{
		split_comma = ft_split(split_line[1], ',');
		ls_data.pos = ft_vec_set_xyz(ft_atof(split_comma[0]),
										ft_atof(split_comma[1]),
										ft_atof(split_comma[2]));
		while (split_comma[i])
			free(split_comma[i++]);
		free(split_comma);
		ls_data.intensity = ft_atof(split_line[2]);
		i = 0;
		split_comma = ft_split(split_line[3], ',');
		ls_data.color = ft_vec_set_xyz(ft_atoi(split_comma[0]),
										ft_atoi(split_comma[1]),
										ft_atoi(split_comma[2]));
		while (split_comma[i])
			free(split_comma[i++]);
		free(split_comma);
		lights.spli = (t_splight*)malloc(sizeof(t_splight));
		*(lights.spli) = ft_splight_set(ls_data.pos, ls_data.intensity, ls_data.color);
		ft_hit_lst_addback(&engine->light_lst, ft_hit_lst_newobj(lights.spli, 10));
	}
	else if (ft_strncmp(split_line[0], "sp", 2))
	{
		split_comma = ft_split(split_line[1], ',');
		ss_data.center = ft_vec_set_xyz(ft_atof(split_comma[0]),
										ft_atof(split_comma[1]),
										ft_atof(split_comma[2]));
		while (split_comma[i])
			free(split_comma[i++]);
		free(split_comma);
		ss_data.diameter = ft_atof(split_line[2]);
		i = 0;
		split_comma = ft_split(split_line[3], ',');
		ss_data.color = ft_vec_set_xyz(ft_atoi(split_comma[0]),
										ft_atoi(split_comma[1]),
										ft_atoi(split_comma[2]));
		while (split_comma[i])
			free(split_comma[i++]);
		free(split_comma);
		objs.sp = (t_sphere*)malloc(sizeof(t_sphere));
		*(objs.sp) = ft_sphere_set(ss_data.center, ss_data.diameter, ss_data.color);
		ft_hit_lst_addback(&engine->obj_lst, ft_hit_lst_newobj(objs.sp, 1));
	}
	else if (ft_strncmp(split_line[0], "pl", 2))
	{
		split_comma = ft_split(split_line[1], ',');
		ps_data.center = ft_vec_set_xyz(ft_atof(split_comma[0]),
										ft_atof(split_comma[1]),
										ft_stof(split_comma[2]));
		while (split_comma[i])
			free(split_comma[i++]);
		free(split_comma);
		i = 0;
		split_comma = ft_split(split_line[2], ',');
		ps_data.norm = ft_vec_set_xyz(ft_atof(split_comma[0]),
										ft_atof(split_comma[1]),
										ft_stof(split_comma[2]));
		while (split_comma[i])
			free(split_comma[i++]);
		free(split_comma);
		i = 0;
		split_comma = ft_split(split_line[3], ',');
		ps_data.color = ft_vec_set_xyz(ft_atoi(split_comma[0]),
										ft_atoi(split_comma[1]),
										ft_stoi(split_comma[2]));
		while (split_comma[i])
			free(split_comma[i++]);
		free(split_comma);
		objs.pl = (t_plane*)malloc(sizeof(t_plane));
		*(objs.pl) = ft_plane_set(ps_data.center, ps_data.norm, ps_data.color);
		ft_hit_lst_addback(&engine->obj_lst, ft_hit_lst_newobj(objs.pl, 2));
	}
	else if (ft_strncmp(split_line[0], "sq", 2))
	{
		split_comma = ft_split(split_line[1], ',');
		ss_data.center = ft_vec_set_xyz(ft_atof(split_comma[0]),
										ft_atof(split_comma[1]),
										ft_stof(split_comma[2]));
		while (split_comma[i])
			free(split_comma[i++]);
		free(split_comma);
		i = 0;
		split_comma = ft_split(split_line[2], ',');
		ss_data.norm = ft_vec_set_xyz(ft_atof(split_comma[0]),
										ft_atof(split_comma[1]),
										ft_stof(split_comma[2]));
		while (split_comma[i])
			free(split_comma[i++]);
		free(split_comma);
		ss_data.side_size = ft_atof(split_line[3]);
		i = 0;
		split_comma = ft_split(split_line[4], ',');
		ss_data.color = ft_vec_set_xyz(ft_atoi(split_comma[0]),
										ft_atoi(split_comma[1]),
										ft_stoi(split_comma[2]));
		while (split_comma[i])
			free(split_comma[i++]);
		free(split_comma);
		objs.sq = (t_square*)malloc(sizeof(t_square));
		*(objs.sq) = ft_square_set(ss_data.center, ss_data.norm, ss_data.side_size,
							ss_data.color);
		ft_hit_lst_addback(&engine->obj_lst, ft_hit_lst_newobj(objs.sq, 3));
	}
	else if (ft_strncmp(split_line[0], "cy", 2))
	{
		split_comma = ft_split(split_line[1], ',');
		cys_data.center = ft_vec_set_xyz(ft_atof(split_comma[0]),
										ft_atof(split_comma[1]),
										ft_stof(split_comma[2]));
		while (split_comma[i])
			free(split_comma[i++]);
		free(split_comma);
		i = 0;
		split_comma = ft_split(split_line[2], ',');
		cys_data.dir = ft_vec_set_xyz(ft_atof(split_comma[0]),
										ft_atof(split_comma[1]),
										ft_stof(split_comma[2]));
		while (split_comma[i])
			free(split_comma[i++]);
		free(split_comma);
		cys_data.diameter = ft_atof(split_line[3]);
		cys_data.h = ft_atof(split_line[4]);
		i = 0;
		split_comma = ft_split(split_line[5], ',');
		cys_data.color = ft_vec_set_xyz(ft_atoi(split_comma[0]),
										ft_atoi(split_comma[1]),
										ft_stoi(split_comma[2]));
		while (split_comma[i])
			free(split_comma[i++]);
		free(split_comma);
		objs.cy = (t_cylinder*)malloc(sizeof(t_cylinder));
		*(objs.cy) = ft_cylinder_set(cys_data.center, cys_data.dir, cys_data.diameter,
									cys_data.h, cys_data.color);
		ft_hit_lst_addback(&engine->obj_lst, ft_hit_lst_newobj(objs.cy, 4));
	}
	else if (ft_strncmp(split_line[0], "tr", 2))
	{
		split_comma = ft_split(split_line[1], ',');
		trs_data.p0 = ft_vec_set_xyz(ft_atof(split_comma[0]),
										ft_atof(split_comma[1]),
										ft_stof(split_comma[2]));
		while (split_comma[i])
			free(split_comma[i++]);
		free(split_comma);
		i = 0;
		split_comma = ft_split(split_line[1], ',');
		trs_data.p1 = ft_vec_set_xyz(ft_atof(split_comma[0]),
										ft_atof(split_comma[1]),
										ft_stof(split_comma[2]));
		while (split_comma[i])
			free(split_comma[i++]);
		free(split_comma);
		i = 0;
		split_comma = ft_split(split_line[1], ',');
		trs_data.p2 = ft_vec_set_xyz(ft_atof(split_comma[0]),
										ft_atof(split_comma[1]),
										ft_stof(split_comma[2]));
		while (split_comma[i])
			free(split_comma[i++]);
		free(split_comma);
		i = 0;
		split_comma = ft_split(split_line[1], ',');
		trs_data.color = ft_vec_set_xyz(ft_atoi(split_comma[0]),
										ft_atoi(split_comma[1]),
										ft_stoi(split_comma[2]));
		while (split_comma[i])
			free(split_comma[i++]);
		free(split_comma);
		objs.tr = (t_triangle*)malloc(sizeof(t_triangle));
		*(objs.tr) = ft_triangle_set(trs_data.p0, trs_data.p1, trs_data.p2,
								trs_data.color);
		ft_hit_lst_addback(&engine->obj_lst, ft_hit_lst_newobj(objs.tr, 5));
	}
}

int	ft_scene_reader(t_engine *engine, char *filename)
{
	char *line;
	int fd;
	int ret;

	line = NULL;
	fd = open(filename, O_RDONLY);
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		ft_line_parser(engine, line);
		ret = get_next_line(fd, &line);
	}
	return (1);
}
