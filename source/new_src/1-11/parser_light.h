/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_light.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:27:21 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/09 17:28:25 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_LIGHT_H
# define PARSER_LIGHT_H
# include "struct_set.h"
# include "parser_util1.h"
# include "parser_util2.h"

int		ft_parse_light(t_engine *engine, char **split_line);

#endif
