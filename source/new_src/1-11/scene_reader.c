/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:47:54 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/07 21:04:39 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_reader.h"
#include <fcntl.h>
#include <unistd.h>

void ft_line_parser(t_engine *engine, char *line)
{
	int					i;
	char				**split_line;
	char				**split_comma;
	t_cams				cams;
	t_cam_scene_data	cs_data;

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
