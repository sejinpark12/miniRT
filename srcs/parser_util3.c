/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 11:22:07 by sejpark           #+#    #+#             */
/*   Updated: 2021/05/23 19:48:29 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser_util.h"

int		ft_count_split(char **split_line)
{
	int	i;

	i = 0;
	while (split_line[i])
		i++;
	return (i);
}

char	**ft_get_split_data(t_engine *engine, char *str, char separator,
			int cnt)
{
	char	**result;

	result = ft_split(str, separator);
	if (result == NULL)
		error_handler("ft_split 함수 메모리 동적할당 실패", engine);
	if (ft_count_split(result) != cnt)
		error_handler("ft_split 함수가 문자열을 정상적으로 나누지 못했습니다.",
				engine);
	return (result);
}

void	ft_add_split_data_to_par_lst(t_engine *engine, char **split_line)
{
	t_par_lst	*new_par_lst;

	new_par_lst = ft_par_lst_new(split_line);
	if (new_par_lst == NULL)
	{
		ft_free_split(split_line);
		error_handler("ft_par_lst_new 함수 메모리 동적할당 실패", engine);
	}
	ft_par_lst_addback(&engine->parser_lst, new_par_lst);
}
