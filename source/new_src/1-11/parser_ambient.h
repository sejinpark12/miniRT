/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ambient.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:10:00 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/10 14:57:42 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_AMBIENT_H
# define PARSER_AMBIENT_H
# include "struct_set.h"
# include "parser_util1.h"
# include "parser_util2.h"
# include "error_handler.h"

void	ft_parse_ambient(t_engine *engine, int *a_chk, char **split_line);

#endif
