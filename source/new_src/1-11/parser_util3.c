/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 11:22:07 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/10 11:32:59 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_util3.h"

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
