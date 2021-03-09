/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util2.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:46:28 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/09 19:30:12 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTIL2_H
# define PARSER_UTIL2_H
# include "libft/libft.h"

int		ft_strcmp(const char *str1, const char *str2);
double	ft_beforepoint(const char *nbr, char **decimal_point, int *length);
double	ft_atof(const char *nbr);
void	ft_free_split(char **split);
int		ft_count_split(char **split_line);
#endif
