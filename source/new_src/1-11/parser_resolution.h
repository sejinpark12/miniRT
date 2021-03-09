/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_resolution.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:17:25 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/09 17:19:54 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_RESOLUTION_H
# define PARSER_RESOLUTION_H
# include "mlx.h"
# include "parser_util1.h"
# include "parser_util2.h"

int		ft_parse_resolution(t_engine *engine, int *r_chk, char **split_line);

#endif
