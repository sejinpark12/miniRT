/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:47:54 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/09 14:31:20 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_reader.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void	ft_free_all(t_engine *engine)
{
	ft_hit_lst_clear(&(engine->cam_lst));
	ft_hit_lst_clear(&(engine->data.img_lst));
	ft_hit_lst_clear(&(engine->obj_lst));
	ft_hit_lst_clear(&(engine->light_lst));
}

int		ft_chk_lightrange(const double intensity)
{
	if (intensity < 0 || intensity > 1)
		return (0);
	return (1);
}

int		ft_chk_dirrange(const t_vec3 dir)
{
	if (dir.x < -1 || dir.x > 1)
		return (0);
	if (dir.y < -1 || dir.y > 1)
		return (0);
	if (dir.z < -1 || dir.z > 1)
		return (0);
	return (1);
}

int		ft_chk_colorrange(const t_color color)
{
	if (color.x < 0 || color.x > 255)
		return (0);
	if (color.y < 0 || color.y > 255)
		return (0);
	if (color.z < 0 || color.z > 255)
		return (0);
	return (1);
}

int		ft_chk_fovrange(const int fov)
{
	if (fov < 0 || fov > 180)
		return (0);
	return (1);
}

int		ft_strcmp(const char *str1, const char *str2)
{
	size_t i;
	size_t str1_len;
	size_t str2_len;

	i = 0;
	str1_len = ft_strlen(str1);
	str2_len = ft_strlen(str2);
	if (str1_len != str2_len)
		return (-1);
	while (str1[i])
	{
		if (str1[i] != str2[i])
			return (-1);
		i++;
	}
	return (0);
}

double	ft_beforepoint(const char *nbr, char **decimal_point, size_t *length)
{
	double	result;
	char	*subnbr;

	*decimal_point = ft_strchr(nbr, '.');
	if (*decimal_point)
	{
		*length = *decimal_point - nbr;
		subnbr = ft_substr(nbr, 0, (*length)++);
	}
	else
	{
		*length = ft_strlen(nbr);
		subnbr = ft_substr(nbr, 0, *length);
	}
	result = ft_atoi(subnbr);
	free(subnbr);
	return (result);
}

double	ft_atof(const char *nbr)
{
	double	result;
	size_t	length;
	double	decimal;
	char	*decimal_point;

	result = 0.0;
	result = ft_beforepoint(nbr, &decimal_point, &length);
	if (result >= 0 && nbr[0] != '-')
		decimal = 1;
	else if (result == 0 && nbr[0] == '-')
		decimal = -1;
	else
		decimal = -1;
	while (nbr[length])
	{
		if (!ft_isdigit(nbr[length]))
			break;
		decimal *= 0.1;
		result += (decimal * (nbr[length++] - '0'));
	}
	return (result);
}

int		ft_parse_resolution(t_engine *engine, int *r_chk, char **split_line)
{
	int result;

	result = 1;
	if (*r_chk == 0)
	{
		mlx_get_screen_size(engine->data.mlx, &engine->data.width,
												&engine->data.height);
		if (ft_atoi(split_line[1]) < engine->data.width &&
				ft_atoi(split_line[2]) < engine->data.height)
		{
			engine->data.width = ft_atoi(split_line[1]);
			engine->data.height = ft_atoi(split_line[2]);
		}
		*r_chk = 1;
	}
	else
		result = -1;
	return (result);
}

void	ft_free_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

int		ft_parse_ambient(t_engine *engine, int *a_chk, char **split_line)
{
	int		result;
	char	**split_comma;

	result = 1;
	if (*a_chk == 0)
	{
		engine->data.ambient.intensity = ft_atof(split_line[1]);
		split_comma = ft_split(split_line[2], ',');
		engine->data.ambient.color.x = ft_atoi(split_comma[0]);
		engine->data.ambient.color.y = ft_atoi(split_comma[1]);
		engine->data.ambient.color.z = ft_atoi(split_comma[2]);
		ft_free_split(split_comma);
		if (ft_chk_colorrange(engine->data.ambient.color) == 0 ||
				ft_chk_lightrange(engine->data.ambient.intensity) == 0)
			result = -1;
		*a_chk = 1;
	}
	else
		result = -1;
	return (result);
}

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
		result = -1;
	else
	{
		cams.cam = (t_camera*)malloc(sizeof(t_camera));
		*(cams.cam) = ft_camera_set(cs_data.viewpoint, cs_data.dir, cs_data.fov);
		ft_hit_lst_addback(&engine->cam_lst, ft_hit_lst_newobj(cams.cam, 20));
	}
	return (result);
}

int		ft_parse_light(t_engine *engine, char **split_line)
{
	int					result;
	char				**split_comma;
	t_lights			lights;
	t_light_scene_data	ls_data;

	result = 1;
	split_comma = ft_split(split_line[1], ',');
	ls_data.pos = ft_vec_set_xyz(ft_atof(split_comma[0]),
							ft_atof(split_comma[1]), ft_atof(split_comma[2]));
	ft_free_split(split_comma);
	ls_data.intensity = ft_atof(split_line[2]);
	split_comma = ft_split(split_line[3], ',');
	ls_data.color = ft_vec_set_xyz(ft_atoi(split_comma[0]),
							ft_atoi(split_comma[1]), ft_atoi(split_comma[2]));
	ft_free_split(split_comma);
	if (ft_chk_lightrange(ls_data.intensity) == 0 ||
							ft_chk_colorrange(ls_data.color) == 0)
		result = -1;
	else
	{
		lights.spli = (t_splight*)malloc(sizeof(t_splight));
		*(lights.spli) = ft_splight_set(ls_data.pos, ls_data.intensity,
										ls_data.color);
		ft_hit_lst_addback(&engine->light_lst,
										ft_hit_lst_newobj(lights.spli, 10));
	}
	return (result);
}

int		ft_parse_sphere(t_engine *engine, char **split_line)
{
	int						result;
	char					**split_comma;
	t_objs					objs;
	t_sphere_scene_data		sps_data;

	result = 1;
	split_comma = ft_split(split_line[1], ',');
	sps_data.center = ft_vec_set_xyz(ft_atof(split_comma[0]),
						ft_atof(split_comma[1]), ft_atof(split_comma[2]));
	ft_free_split(split_comma);
	sps_data.diameter = ft_atof(split_line[2]);
	split_comma = ft_split(split_line[3], ',');
	sps_data.color = ft_vec_set_xyz(ft_atoi(split_comma[0]),
						ft_atoi(split_comma[1]), ft_atoi(split_comma[2]));
	ft_free_split(split_comma);
	if (ft_chk_colorrange(sps_data.color) == 0)
		result = -1;
	else
	{
		objs.sp = (t_sphere*)malloc(sizeof(t_sphere));
		*(objs.sp) = ft_sphere_set(sps_data.center, sps_data.diameter,
										sps_data.color);
		ft_hit_lst_addback(&engine->obj_lst, ft_hit_lst_newobj(objs.sp, 1));
	}
	return (result);
}

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
		result = -1;
	else
	{
		objs.pl = (t_plane*)malloc(sizeof(t_plane));
		*(objs.pl) = ft_plane_set(ps_data.center, ps_data.norm, ps_data.color);
		ft_hit_lst_addback(&engine->obj_lst, ft_hit_lst_newobj(objs.pl, 2));
	}
	return (result);
}

int		ft_parse_square(t_engine *engine, char **split_line)
{
	int						result;
	char					**split_comma;
	t_objs					objs;
	t_square_scene_data		sqs_data;

	result = 1;
	split_comma = ft_split(split_line[1], ',');
	sqs_data.center = ft_vec_set_xyz(ft_atof(split_comma[0]),
					ft_atof(split_comma[1]), ft_atof(split_comma[2]));
	ft_free_split(split_comma);
	split_comma = ft_split(split_line[2], ',');
	sqs_data.norm = ft_vec_set_xyz(ft_atof(split_comma[0]),
					ft_atof(split_comma[1]), ft_atof(split_comma[2]));
	ft_free_split(split_comma);
	sqs_data.side_size = ft_atof(split_line[3]);
	split_comma = ft_split(split_line[4], ',');
	sqs_data.color = ft_vec_set_xyz(ft_atoi(split_comma[0]),
					ft_atoi(split_comma[1]), ft_atoi(split_comma[2]));
	ft_free_split(split_comma);
	if (ft_chk_dirrange(sqs_data.norm) == 0 ||
									ft_chk_colorrange(sqs_data.color) == 0)
		result = -1;
	else
	{
		objs.sq = (t_square*)malloc(sizeof(t_square));
		*(objs.sq) = ft_square_set(sqs_data.center, sqs_data.norm,
								sqs_data.side_size, sqs_data.color);
		ft_hit_lst_addback(&engine->obj_lst, ft_hit_lst_newobj(objs.sq, 3));
	}
	return (result);
}

int		ft_parse_cylinder(t_engine *engine, char **split_line)
{
	int						result;
	char					**split_comma;
	t_objs					objs;
	t_cylinder_scene_data	cys_data;

	result = 1;
	split_comma = ft_split(split_line[1], ',');
	cys_data.center = ft_vec_set_xyz(ft_atof(split_comma[0]),
					ft_atof(split_comma[1]), ft_atof(split_comma[2]));
	ft_free_split(split_comma);
	split_comma = ft_split(split_line[2], ',');
	cys_data.dir = ft_vec_set_xyz(ft_atof(split_comma[0]),
					ft_atof(split_comma[1]), ft_atof(split_comma[2]));
	ft_free_split(split_comma);
	cys_data.diameter = ft_atof(split_line[3]);
	cys_data.h = ft_atof(split_line[4]);
	split_comma = ft_split(split_line[5], ',');
	cys_data.color = ft_vec_set_xyz(ft_atoi(split_comma[0]),
					ft_atoi(split_comma[1]), ft_atoi(split_comma[2]));
	ft_free_split(split_comma);
	if (ft_chk_dirrange(cys_data.dir) == 0 ||
								ft_chk_colorrange(cys_data.color) == 0)
		result = -1;
	else
	{
		objs.cy = (t_cylinder*)malloc(sizeof(t_cylinder));
//		*(objs.cy) = ft_cylinder_set(cys_data.center, cys_data.dir,
//				    cys_data.diameter, cys_data.h, cys_data.color);
		*(objs.cy) = ft_cylinder_set(&cys_data);
		ft_hit_lst_addback(&engine->obj_lst, ft_hit_lst_newobj(objs.cy, 4));
	}
	return (result);
}

int		ft_parse_triangle(t_engine *engine, char **split_line)
{
	int						result;
	char					**split_comma;
	t_objs					objs;
	t_triangle_scene_data	trs_data;

	result = 1;
	split_comma = ft_split(split_line[1], ',');
	trs_data.p0 = ft_vec_set_xyz(ft_atof(split_comma[0]),
					ft_atof(split_comma[1]), ft_atof(split_comma[2]));
	ft_free_split(split_comma);
	split_comma = ft_split(split_line[2], ',');
	trs_data.p1 = ft_vec_set_xyz(ft_atof(split_comma[0]),
					ft_atof(split_comma[1]), ft_atof(split_comma[2]));
	ft_free_split(split_comma);
	split_comma = ft_split(split_line[3], ',');
	trs_data.p2 = ft_vec_set_xyz(ft_atof(split_comma[0]),
					ft_atof(split_comma[1]), ft_atof(split_comma[2]));
	ft_free_split(split_comma);
	split_comma = ft_split(split_line[4], ',');
	trs_data.color = ft_vec_set_xyz(ft_atoi(split_comma[0]),
					ft_atoi(split_comma[1]), ft_atoi(split_comma[2]));
	ft_free_split(split_comma);
	if (ft_chk_colorrange(trs_data.color) == 0)
		result = -1;
	else
	{
		objs.tr = (t_triangle*)malloc(sizeof(t_triangle));
		*(objs.tr) = ft_triangle_set(trs_data.p0, trs_data.p1, trs_data.p2,
								trs_data.color);
		ft_hit_lst_addback(&engine->obj_lst, ft_hit_lst_newobj(objs.tr, 5));
	}
	return (result);
}

int		ft_line_parser(t_engine *engine, char *line, int *r_chk, int *a_chk)
{
	int		result;
	char	**split_line;

	result = 1;
	split_line = ft_split(line, ' ');
	if (split_line[0][0] == 'R')
		result = ft_parse_resolution(engine, r_chk, split_line);
	else if (split_line[0][0] == 'A')
		result = ft_parse_ambient(engine, a_chk, split_line);
	else if (ft_strcmp(split_line[0], "c") == 0)
		result = ft_parse_camera(engine, split_line);
	else if (ft_strcmp(split_line[0], "l") == 0)
		result = ft_parse_light(engine, split_line);
	else if (ft_strcmp(split_line[0], "sp") == 0)
		result = ft_parse_sphere(engine, split_line);
	else if (ft_strcmp(split_line[0], "pl") == 0)
		result = ft_parse_plane(engine, split_line);
	else if (ft_strcmp(split_line[0], "sq") == 0)
		result = ft_parse_square(engine, split_line);
	else if (ft_strcmp(split_line[0], "cy") == 0)
		result = ft_parse_cylinder(engine, split_line);
	else if (ft_strcmp(split_line[0], "tr") == 0)
		result = ft_parse_triangle(engine, split_line);
	else
		result = -1;
	ft_free_split(split_line);
	return (result);
}

int	ft_scene_reader(t_engine *engine, char *filename)
{
	char	*line;
	int		fd;
	int		ret;
	int		r_chk;
	int		a_chk;

	line = NULL;
	fd = open(filename, O_RDONLY);
	ret = get_next_line(fd, &line);
	r_chk = 0;
	a_chk = 0;
	while (ret > 0)
	{
		if (ft_strcmp(line, ""))
		{
			if (ft_line_parser(engine, line, &r_chk, &a_chk) == -1)
			{
				free(line);
				close(fd);
				return (-1);
			}
		}
		free(line);
		ret = get_next_line(fd, &line);
	}
	if (ft_strcmp(line, ""))
	{
		if (ft_line_parser(engine, line, &r_chk, &a_chk) == -1)
		{
			free(line);
			close(fd);
			return (-1);
		}
	}
	free(line);
	close(fd);
	return (1);
}
