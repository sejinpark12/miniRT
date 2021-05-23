/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:47:56 by sejpark           #+#    #+#             */
/*   Updated: 2021/05/23 19:48:29 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser_util.h"

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

double	ft_beforepoint(const char *nbr, char **decimal_point, int *length,
			t_engine *engine)
{
	double	result;
	char	*subnbr;

	subnbr = NULL;
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
	if (subnbr == NULL)
		error_handler("메모리 동적할당 실패했습니다.", engine);
	result = ft_atoi_minirt(subnbr, engine);
	free(subnbr);
	return (result);
}

double	ft_atof(const char *nbr, t_engine *engine)
{
	double	result;
	int		length;
	double	decimal;
	char	*decimal_point;

	result = 0.0;
	result = ft_beforepoint(nbr, &decimal_point, &length, engine);
	if (result >= 0 && nbr[0] != '-')
		decimal = 1;
	else if (result == 0 && nbr[0] == '-')
		decimal = -1;
	else
		decimal = -1;
	while (nbr[length])
	{
		if (!ft_isdigit(nbr[length]))
			error_handler("잘못된 데이터 타입의 값이 입력되었습니다.", engine);
		decimal *= 0.1;
		result += (decimal * (nbr[length++] - '0'));
	}
	return (result);
}

int		ft_atoi_minirt(char *str, t_engine *engine)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
		{
			free(str);
			error_handler("잘못된 데이터 타입의 값이 입력되었습니다.", engine);
		}
		i++;
	}
	return (ft_atoi(str));
}
