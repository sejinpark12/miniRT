/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_plane.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:34:54 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/11 11:08:12 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_PLANE_H
# define PARSER_PLANE_H
# include "struct_set.h"
# include "parser_util.h"
# include "error_handler.h"

void	ft_alloc_plane(t_engine *engine, char **split_line);

#endif
