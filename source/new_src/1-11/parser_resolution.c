/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_resolution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:18:59 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/09 18:57:51 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_resolution.h"

int		ft_parse_resolution(t_engine *engine, int *r_chk, char **split_line)
{
	int result;

	result = 1;
	if (*r_chk == 0)
	{
		mlx_get_screen_size(engine->data.mlx, &engine->data.width,
												&engine->data.height);
		if (ft_atoi(split_line[1]) < engine->data.width &&
				ft_atoi(split_line[2]) < engine->data.height)
		{
			engine->data.width = ft_atoi(split_line[1]);
			engine->data.height = ft_atoi(split_line[2]);
		}
		*r_chk = 1;
	}
	else
		result = 0;
	return (result);
}
