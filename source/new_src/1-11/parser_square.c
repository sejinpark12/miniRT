/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_square.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:48:23 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/10 10:50:26 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_square.h"

int		ft_parse_square(t_engine *engine, char **split_line)
{
	int						result;
	char					**split_comma;
	t_objs					objs;
	t_square_scene_data		sqs_data;

	result = 1;
	split_comma = ft_split(split_line[1], ',');
	sqs_data.center = ft_vec_set_xyz(ft_atof(split_comma[0], engine),
		ft_atof(split_comma[1], engine), ft_atof(split_comma[2], engine));
	ft_free_split(split_comma);
	split_comma = ft_split(split_line[2], ',');
	sqs_data.norm = ft_vec_set_xyz(ft_atof(split_comma[0], engine),
		ft_atof(split_comma[1], engine), ft_atof(split_comma[2], engine));
	ft_free_split(split_comma);
	sqs_data.side_size = ft_atof(split_line[3], engine);
	split_comma = ft_split(split_line[4], ',');
	sqs_data.color = ft_vec_set_xyz(ft_atoi(split_comma[0]),
					ft_atoi(split_comma[1]), ft_atoi(split_comma[2]));
	ft_free_split(split_comma);
	if (ft_chk_dirrange(sqs_data.norm) == 0 ||
									ft_chk_colorrange(sqs_data.color) == 0)
		result = 0;
	else
	{
		objs.sq = (t_square*)malloc(sizeof(t_square));
		*(objs.sq) = ft_square_set(sqs_data.center, sqs_data.norm,
								sqs_data.side_size, sqs_data.color);
		ft_hit_lst_addback(&engine->obj_lst, ft_hit_lst_newobj(objs.sq, 3));
	}
	return (result);
}
