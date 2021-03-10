/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:47:54 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/10 17:21:40 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_reader.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void	ft_element_parser(t_engine *engine, char **split_line, int *r_chk,
		int *a_chk)
{
	if (ft_strcmp(split_line[0], "R") == 0)
		ft_parse_resolution(engine, r_chk, split_line);
	else if (ft_strcmp(split_line[0], "A") == 0)
		ft_parse_ambient(engine, a_chk, split_line);
	else if (ft_strcmp(split_line[0], "c") == 0)
		ft_alloc_camera(engine, split_line);
	else if (ft_strcmp(split_line[0], "l") == 0)
		ft_parse_light(engine, split_line);
	else if (ft_strcmp(split_line[0], "sp") == 0)
		ft_parse_sphere(engine, split_line);
	else if (ft_strcmp(split_line[0], "pl") == 0)
		ft_parse_plane(engine, split_line);
	else if (ft_strcmp(split_line[0], "sq") == 0)
		ft_parse_square(engine, split_line);
	else if (ft_strcmp(split_line[0], "cy") == 0)
		ft_parse_cylinder(engine, split_line);
	else if (ft_strcmp(split_line[0], "tr") == 0)
		ft_parse_triangle(engine, split_line);
}

void	ft_line_parser_chk(char **split_line, t_engine *engine)
{
	int	i;

	i = ft_count_split(split_line);
	if (i < 3 || i > 6)
		error_handler("잘못된 element 정보가 입력되었습니다.", engine);
	if (ft_strcmp(split_line[0], "R") == 0 && i == 3)
		return ;
	else if (ft_strcmp(split_line[0], "A") == 0 && i == 3)
		return ;
	else if (ft_strcmp(split_line[0], "c") == 0 && i == 4)
		return ;
	else if (ft_strcmp(split_line[0], "l") == 0 && i == 4)
		return ;
	else if (ft_strcmp(split_line[0], "sp") == 0 && i == 4)
		return ;
	else if (ft_strcmp(split_line[0], "pl") == 0 && i == 4)
		return ;
	else if (ft_strcmp(split_line[0], "sq") == 0 && i == 5)
		return ;
	else if (ft_strcmp(split_line[0], "cy") == 0 && i == 6)
		return ;
	else if (ft_strcmp(split_line[0], "tr") == 0 && i == 5)
		return ;
	error_handler("잘못된 element 정보가 입력되었습니다.", engine);
}

void	ft_line_parser(t_engine *engine, char *line, int *r_chk, int *a_chk)
{
	char		**split_line;
	t_par_lst	*new_par_lst;

	split_line = ft_split(line, ' ');
	if (split_line == NULL)
		error_handler("ft_split 함수 메모리 동적할당 실패", engine);
	ft_line_parser_chk(split_line, engine);
	new_par_lst = ft_par_lst_new(split_line);
	if (new_par_lst == NULL)
		error_handler("ft_par_lst_new 함수 메모리 동적할당 실패", engine);
	ft_par_lst_addback(&engine->parser_lst, new_par_lst);
	ft_element_parser(engine, split_line, r_chk, a_chk);
}

t_file_info	ft_file_set(char *filename, t_engine *engine)
{
	t_file_info	fi;

	fi.line = NULL;
	fi.fd = open(filename, O_RDONLY);
	if (fi.fd == -1)
		error_handler("파일을 열 수 없습니다.", engine);
	fi.ret = get_next_line(fi.fd, &fi.line);
	fi.r_chk = 0;
	fi.a_chk = 0;
	return (fi);
}

int		ft_scene_reader(t_engine *engine, char *filename)
{
	t_file_info	fi;

	fi = ft_file_set(filename, engine);
	while (fi.ret > 0)
	{
		if (ft_strcmp(fi.line, "") != 0)
			ft_line_parser(engine, fi.line, &fi.r_chk, &fi.a_chk);
		free(fi.line);
		fi.ret = get_next_line(fi.fd, &fi.line);
	}
	if (ft_strcmp(fi.line, "") != 0)
		ft_line_parser(engine, fi.line, &fi.r_chk, &fi.a_chk);
	free(fi.line);
	close(fi.fd);
	return (1);
}
