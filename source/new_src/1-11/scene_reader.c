/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:47:54 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/09 21:08:09 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_reader.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int			ft_element_parser(t_engine *engine, char **split_line, int *r_chk,
		int *a_chk)
{
	if (split_line[0][0] == 'R')
		return (ft_parse_resolution(engine, r_chk, split_line));
	else if (split_line[0][0] == 'A')
		return (ft_parse_ambient(engine, a_chk, split_line));
	else if (ft_strcmp(split_line[0], "c") == 0)
		return (ft_parse_camera(engine, split_line));
	else if (ft_strcmp(split_line[0], "l") == 0)
		return (ft_parse_light(engine, split_line));
	else if (ft_strcmp(split_line[0], "sp") == 0)
		return (ft_parse_sphere(engine, split_line));
	else if (ft_strcmp(split_line[0], "pl") == 0)
		return (ft_parse_plane(engine, split_line));
	else if (ft_strcmp(split_line[0], "sq") == 0)
		return (ft_parse_square(engine, split_line));
	else if (ft_strcmp(split_line[0], "cy") == 0)
		return (ft_parse_cylinder(engine, split_line));
	else if (ft_strcmp(split_line[0], "tr") == 0)
		return (ft_parse_triangle(engine, split_line));
	else
		return (0);
}

int			ft_line_parser_chk(char **split_line)
{
	int	i;

	i = ft_count_split(split_line);
	if (i < 3 || i > 6)
		return (0);
	if (ft_strcmp(split_line[0], "R") == 0 && i == 3)
		return (1);
	else if (ft_strcmp(split_line[0], "A") == 0 && i == 3)
		return (1);
	else if (ft_strcmp(split_line[0], "c") == 0 && i == 4)
		return (1);
	else if (ft_strcmp(split_line[0], "l") == 0 && i == 4)
		return (1);
	else if (ft_strcmp(split_line[0], "sp") == 0 && i == 4)
		return (1);
	else if (ft_strcmp(split_line[0], "pl") == 0 && i == 4)
		return (1);
	else if (ft_strcmp(split_line[0], "sq") == 0 && i == 5)
		return (1);
	else if (ft_strcmp(split_line[0], "cy") == 0 && i == 6)
		return (1);
	else if (ft_strcmp(split_line[0], "tr") == 0 && i == 5)
		return (1);
	return (0);
}

int			ft_line_parser(t_engine *engine, char *line, int *r_chk, int *a_chk)
{
	int		result;
	char	**split_line;

	split_line = ft_split(line, ' ');
	if (ft_line_parser_chk(split_line) == 0)
		result = 0;
	else
		result = ft_element_parser(engine, split_line, r_chk, a_chk);
	ft_free_split(split_line);
	return (result);
}

t_file_info	ft_file_set(char *filename)
{
	t_file_info	fi;

	fi.line = NULL;
	fi.fd = open(filename, O_RDONLY);
	fi.ret = get_next_line(fi.fd, &fi.line);
	fi.r_chk = 0;
	fi.a_chk = 0;
	return (fi);
}

int			ft_scene_reader(t_engine *engine, char *filename)
{
	t_file_info	fi;

	fi = ft_file_set(filename);
	while (fi.ret > 0)
	{
		if (ft_strcmp(fi.line, "") &&
			ft_line_parser(engine, fi.line, &fi.r_chk, &fi.a_chk) == 0)
		{
			free(fi.line);
			close(fi.fd);
			return (-1);
		}
		free(fi.line);
		fi.ret = get_next_line(fi.fd, &fi.line);
	}
	if (ft_strcmp(fi.line, "") &&
			ft_line_parser(engine, fi.line, &fi.r_chk, &fi.a_chk) == 0)
	{
		free(fi.line);
		close(fi.fd);
		return (-1);
	}
	free(fi.line);
	close(fi.fd);
	return (1);
}
