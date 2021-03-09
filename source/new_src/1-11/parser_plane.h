/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_plane.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:34:54 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/09 17:36:18 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_PLANE_H
# define PARSER_PLANE_H
# include "struct_set.h"
# include "parser_util1.h"
# include "parser_util2.h"

int		ft_parse_plane(t_engine *engine, char **split_line);

#endif
