/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util2.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:46:28 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/10 13:58:24 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTIL2_H
# define PARSER_UTIL2_H
# include "libft/libft.h"
# include "error_handler.h"
# include "parser_util3.h"

int		ft_strcmp(const char *str1, const char *str2);
double	ft_beforepoint(const char *nbr, char **decimal_point, int *length,
			t_engine *engine);
double	ft_atof(const char *nbr, t_engine *engine);
int		ft_count_split(char **split_line);
#endif
