/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_resolution.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:17:25 by sejpark           #+#    #+#             */
/*   Updated: 2021/05/23 20:13:42 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_RESOLUTION_H
# define PARSER_RESOLUTION_H
# include "../library/mlx/includes/mlx.h"
# include "parser_util.h"

void	ft_parse_resolution(t_engine *engine, int *r_chk, char **split_line);

#endif
