/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:47:56 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/09 19:29:58 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_util2.h"

int		ft_strcmp(const char *str1, const char *str2)
{
	int i;
	int str1_len;
	int str2_len;

	i = 0;
	str1_len = ft_strlen(str1);
	str2_len = ft_strlen(str2);
	if (str1_len != str2_len)
		return (-1);
	while (str1[i])
	{
		if (str1[i] != str2[i])
			return (-1);
		i++;
	}
	return (0);
}

double	ft_beforepoint(const char *nbr, char **decimal_point, int *length)
{
	double	result;
	char	*subnbr;

	*decimal_point = ft_strchr(nbr, '.');
	if (*decimal_point)
	{
		*length = *decimal_point - nbr;
		subnbr = ft_substr(nbr, 0, (*length)++);
	}
	else
	{
		*length = ft_strlen(nbr);
		subnbr = ft_substr(nbr, 0, *length);
	}
	result = ft_atoi(subnbr);
	free(subnbr);
	return (result);
}

double	ft_atof(const char *nbr)
{
	double	result;
	int	length;
	double	decimal;
	char	*decimal_point;

	result = 0.0;
	result = ft_beforepoint(nbr, &decimal_point, &length);
	if (result >= 0 && nbr[0] != '-')
		decimal = 1;
	else if (result == 0 && nbr[0] == '-')
		decimal = -1;
	else
		decimal = -1;
	while (nbr[length])
	{
		if (!ft_isdigit(nbr[length]))
			break;
		decimal *= 0.1;
		result += (decimal * (nbr[length++] - '0'));
	}
	return (result);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

int		ft_count_split(char **split_line)
{
	int	i;

	i = 0;
	while (split_line[i])
		i++;
	return (i);
}
