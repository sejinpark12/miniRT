/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_square.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:48:23 by sejpark           #+#    #+#             */
/*   Updated: 2021/05/23 19:48:29 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser_square.h"

void	ft_parse_square(t_engine *engine, char **split_line,
				t_square_scene_data *sqs_data)
{
	char	**split_comma;

	split_comma = ft_get_split_data(engine, split_line[1], ',', 3);
	sqs_data->center = ft_vec_set_xyz(ft_atof(split_comma[0], engine),
										ft_atof(split_comma[1], engine),
										ft_atof(split_comma[2], engine));
	ft_add_split_data_to_par_lst(engine, split_comma);
	split_comma = ft_get_split_data(engine, split_line[2], ',', 3);
	sqs_data->norm = ft_vec_set_xyz(ft_atof(split_comma[0], engine),
									ft_atof(split_comma[1], engine),
									ft_atof(split_comma[2], engine));
	ft_add_split_data_to_par_lst(engine, split_comma);
	sqs_data->side_size = ft_atof(split_line[3], engine);
	split_comma = ft_get_split_data(engine, split_line[4], ',', 3);
	sqs_data->color = ft_vec_set_xyz(ft_atoi_minirt(split_comma[0], engine),
									ft_atoi_minirt(split_comma[1], engine),
									ft_atoi_minirt(split_comma[2], engine));
	ft_add_split_data_to_par_lst(engine, split_comma);
	if (ft_chk_dirrange(sqs_data->norm) == 0 ||
									ft_chk_colorrange(sqs_data->color) == 0)
		error_handler("square의 데이터 범위가 잘못되었습니다.", engine);
}

void	ft_alloc_square(t_engine *engine, char **split_line)
{
	t_objs					objs;
	t_square_scene_data		sqs_data;
	t_obj_lst				*new_obj_lst;

	ft_parse_square(engine, split_line, &sqs_data);
	objs.sq = (t_square*)malloc(sizeof(t_square));
	if (objs.sq == NULL)
		error_handler("square 메모리 동적할당 실패", engine);
	*(objs.sq) = ft_square_set(sqs_data.center, sqs_data.norm,
							sqs_data.side_size, sqs_data.color);
	new_obj_lst = ft_hit_lst_newobj(objs.sq, 3);
	if (new_obj_lst == NULL)
		error_handler("ft_hit_lst_newobj 메모리 동적할당 실패", engine);
	ft_hit_lst_addback(&engine->obj_lst, new_obj_lst);
}
