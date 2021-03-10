/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ambient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:11:41 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/10 23:30:10 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_ambient.h"

void	ft_parse_ambient(t_engine *engine, int *a_chk, char **split_line)
{
	char		**split_comma;
	t_par_lst	*new_par_lst;

	if (*a_chk == 0)
	{
		engine->data.ambient.intensity = ft_atof(split_line[1], engine);
		split_comma = ft_split(split_line[2], ',');
		if (split_comma == NULL)
			error_handler("ft_split 함수 메모리 동적할당 실패", engine);
		new_par_lst = ft_par_lst_new(split_comma);
		if (new_par_lst == NULL)
			error_handler("ft_par_lst_new 함수 메모리 동적할당 실패", engine);
		ft_par_lst_addback(&engine->parser_lst, new_par_lst);
		engine->data.ambient.color.x = ft_atoi_minirt(split_comma[0], engine);
		engine->data.ambient.color.y = ft_atoi_minirt(split_comma[1], engine);
		engine->data.ambient.color.z = ft_atoi_minirt(split_comma[2], engine);
		if (ft_chk_colorrange(engine->data.ambient.color) == 0 ||
				ft_chk_lightrange(engine->data.ambient.intensity) == 0)
			error_handler("Ambient의 데이터 범위가 잘못 되었습니다.", engine);
		*a_chk = 1;
	}
	else
		error_handler("Ambient가 중복되었습니다.", engine);
}
