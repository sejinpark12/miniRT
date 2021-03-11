/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_camera.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 17:21:58 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/11 11:07:52 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_CAMERA_H
# define PARSER_CAMERA_H
# include "struct_set.h"
# include "parser_util.h"

void	ft_alloc_camera(t_engine *engine, char **split_line);

#endif
