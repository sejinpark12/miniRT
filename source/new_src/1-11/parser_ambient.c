/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ambient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:11:41 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/09 21:09:45 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_ambient.h"

int		ft_atoi_chk(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int		ft_atof_chk(char *str)
{
	int	i;
	int point_chk;

	i = 0;
	point_chk = 0;
	if (str[0] == '.')
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] == '.' && point_chk == 0)
			point_chk = 1;
		else if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int		ft_parse_ambient(t_engine *engine, int *a_chk, char **split_line)
{
	int		result;
	char	**split_comma;

	result = 1;
	if (*a_chk == 0)
	{
		engine->data.ambient.intensity = ft_atof(split_line[1]);
		split_comma = ft_split(split_line[2], ',');
		engine->data.ambient.color.x = ft_atoi(split_comma[0]);
		engine->data.ambient.color.y = ft_atoi(split_comma[1]);
		engine->data.ambient.color.z = ft_atoi(split_comma[2]);
		ft_free_split(split_comma);
		if (ft_chk_colorrange(engine->data.ambient.color) == 0 ||
				ft_chk_lightrange(engine->data.ambient.intensity) == 0)
			result = 0;
		*a_chk = 1;
	}
	else
		result = 0;
	return (result);
}
