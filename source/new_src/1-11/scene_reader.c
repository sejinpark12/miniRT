/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:47:54 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/04 16:55:17 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_reader.h"
#include <fcntl.h>
#include <unistd.h>

void ft_line_parser(t_engine *engine, char *line)
{
	int i;
	char **split_line;
	char **split_comma;

	i = 0;
	split_line = ft_split(line, ' ');
	if (splilt_line[0] == 'R')
	{
		engine->data.width = ft_atoi(split_line[1]);
		engine->data.height = ft_atoi(split_line[2]);
	}
	else if (split_line[0] == 'A')
	{
		split_comma = ft_split(split_line[2], ',');
		engine->data.ambient.intensity = ;
		engine->data.ambient.color.x = ft_atoi(split_comma[0]);
		engine->data.ambient.color.y = ft_atoi(split_comma[1]);
		engine->data.ambient.color.z = ft_atoi(split_comma[2]);
		while (split_comma[i])
			free(split_comma[i++]);
		free(split_comma);
	}
}

int	ft_scene_reader(t_engine *engine, char *filename)
{
	char *line;
	int fd;
	int ret;

	line = NULL:
	fd = open(filename, O_RDONLY);
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		ft_line_parser(line);
		ret = get_next_line(fd, &line);
	}
	return (1);
}
