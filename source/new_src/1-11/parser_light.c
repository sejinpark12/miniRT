/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:28:34 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/10 10:49:20 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_light.h"

int		ft_parse_light(t_engine *engine, char **split_line)
{
	int					result;
	char				**split_comma;
	t_lights			lights;
	t_light_scene_data	ls_data;

	result = 1;
	split_comma = ft_split(split_line[1], ',');
	ls_data.pos = ft_vec_set_xyz(ft_atof(split_comma[0], engine),
		ft_atof(split_comma[1], engine), ft_atof(split_comma[2], engine));
	ft_free_split(split_comma);
	ls_data.intensity = ft_atof(split_line[2], engine);
	split_comma = ft_split(split_line[3], ',');
	ls_data.color = ft_vec_set_xyz(ft_atoi(split_comma[0]),
							ft_atoi(split_comma[1]), ft_atoi(split_comma[2]));
	ft_free_split(split_comma);
	if (ft_chk_lightrange(ls_data.intensity) == 0 ||
							ft_chk_colorrange(ls_data.color) == 0)
		result = 0;
	else
	{
		lights.spli = (t_splight*)malloc(sizeof(t_splight));
		*(lights.spli) = ft_splight_set(ls_data.pos, ls_data.intensity,
										ls_data.color);
		ft_hit_lst_addback(&engine->light_lst,
										ft_hit_lst_newobj(lights.spli, 10));
	}
	return (result);
}
