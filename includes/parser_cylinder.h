/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cylinder.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:50:53 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/11 12:11:55 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_CYLINDER_H
# define PARSER_CYLINDER_H
# include "struct_set.h"
# include "parser_util.h"

void	ft_alloc_cylinder(t_engine *engine, char **split_line);

#endif
