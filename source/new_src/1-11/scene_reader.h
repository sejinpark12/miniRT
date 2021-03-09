/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_reader.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:21:49 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/09 18:01:33 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_READER_H
# define SCENE_READER_H
# include "mlx.h"
# include "get_next_line.h"
# include "libft/libft.h"
# include "vec.h"
# include "ray.h"
# include "hittable_list.h"
# include "random.h"
# include "camera.h"
# include "sphere.h"
# include "plane.h"
# include "square.h"
# include "cylinder.h"
# include "triangle.h"
# include "light.h"
# include "struct_set.h"
# include "parser_util1.h"
# include "parser_util2.h"
# include "parser_resolution.h"
# include "parser_ambient.h"
# include "parser_camera.h"
# include "parser_light.h"
# include "parser_sphere.h"
# include "parser_plane.h"
# include "parser_square.h"
# include "parser_cylinder.h"
# include "parser_triangle.h"

int		ft_line_parser(t_engine *engine, char *line, int *r_chk, int *a_chk);
int		ft_scene_reader(t_engine *engine, char *filename);
#endif
