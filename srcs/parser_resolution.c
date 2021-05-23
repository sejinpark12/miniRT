/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_resolution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:18:59 by sejpark           #+#    #+#             */
/*   Updated: 2021/05/23 19:48:29 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser_resolution.h"

void	ft_parse_resolution(t_engine *engine, int *r_chk, char **split_line)
{
	if (*r_chk == 0)
	{
		mlx_get_screen_size(engine->data.mlx, &engine->data.width,
												&engine->data.height);
		if (ft_atoi_minirt(split_line[1], engine) < engine->data.width &&
				ft_atoi_minirt(split_line[2], engine) < engine->data.height)
		{
			engine->data.width = ft_atoi(split_line[1]);
			engine->data.height = ft_atoi(split_line[2]);
		}
		*r_chk = 1;
	}
	else
		error_handler("resolution이 중복되었습니다.", engine);
}
