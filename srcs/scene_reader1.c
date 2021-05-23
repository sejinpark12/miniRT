/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_reader1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:47:54 by sejpark           #+#    #+#             */
/*   Updated: 2021/05/23 19:48:29 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scene_reader.h"
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
		ft_alloc_light(engine, split_line);
	else if (ft_strcmp(split_line[0], "sp") == 0)
		ft_alloc_sphere(engine, split_line);
	else if (ft_strcmp(split_line[0], "pl") == 0)
		ft_alloc_plane(engine, split_line);
	else if (ft_strcmp(split_line[0], "sq") == 0)
		ft_alloc_square(engine, split_line);
	else if (ft_strcmp(split_line[0], "cy") == 0)
		ft_alloc_cylinder(engine, split_line);
	else if (ft_strcmp(split_line[0], "tr") == 0)
		ft_alloc_triangle(engine, split_line);
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

void	ft_file_set(char *filename, t_engine *engine)
{
	engine->data.fi.line = NULL;
	engine->data.fi.fd = open(filename, O_RDONLY);
	if (engine->data.fi.fd == -1)
		error_handler("파일을 열 수 없습니다.", engine);
	engine->data.fi.ret = get_next_line(engine->data.fi.fd,
			&(engine->data.fi.line));
	if (engine->data.fi.ret == -1)
		error_handler("get next line 오류", engine);
	engine->data.fi.r_chk = 0;
	engine->data.fi.a_chk = 0;
}

void	ft_check_rtfile(const char *filename, t_engine *engine)
{
	char	**split_line;
	int		cnt;

	split_line = ft_split(filename, '.');
	if (split_line == NULL)
		error_handler("ft_split 함수 메모리 동적할당 실패", engine);
	ft_add_split_data_to_par_lst(engine, split_line);
	cnt = ft_count_split(split_line);
	if (cnt != 2)
		error_handler("열 수 없는 파일입니다.", engine);
	if (ft_strcmp(split_line[0], "") == 0 ||
			ft_strcmp(split_line[1], "rt") != 0)
		error_handler("열 수 없는 파일입니다.", engine);
}

void	ft_line_parser(t_engine *engine, char *line, int *r_chk, int *a_chk)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	if (split_line == NULL)
		error_handler("ft_split 함수 메모리 동적할당 실패", engine);
	ft_add_split_data_to_par_lst(engine, split_line);
	ft_line_parser_chk(split_line, engine);
	ft_element_parser(engine, split_line, r_chk, a_chk);
}
