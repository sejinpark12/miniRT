/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cylinder.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:50:53 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/09 17:51:51 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_CYLINDER_H
# define PARSER_CYLINDER_H
# include "struct_set.h"
# include "parser_util1.h"
# include "parser_util2.h"

int		ft_parse_cylinder(t_engine *engine, char **split_line);

#endif
