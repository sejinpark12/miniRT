/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ambient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:11:41 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/11 11:54:37 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_ambient.h"

void	ft_parse_ambient(t_engine *engine, int *a_chk, char **split_line)
{
	char		**split_comma;

	if (*a_chk == 0)
	{
		engine->data.ambient.intensity = ft_atof(split_line[1], engine);
		split_comma = ft_get_split_data(engine, split_line[2], ',');
		engine->data.ambient.color = ft_vec_set_xyz(
								ft_atoi_minirt(split_comma[0], engine),
								ft_atoi_minirt(split_comma[1], engine),
								ft_atoi_minirt(split_comma[2], engine));
		ft_add_split_data_to_par_lst(engine, split_comma);
		if (ft_chk_colorrange(engine->data.ambient.color) == 0 ||
				ft_chk_lightrange(engine->data.ambient.intensity) == 0)
			error_handler("Ambient의 데이터 범위가 잘못 되었습니다.", engine);
		*a_chk = 1;
	}
	else
		error_handler("Ambient가 중복되었습니다.", engine);
}
