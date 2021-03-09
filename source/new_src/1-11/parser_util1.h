/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util1.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:26:12 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/09 16:43:32 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTIL1_H
# define PARSER_UTIL1_H
# include "struct_set.h"
# include "vec.h"
# include "hittable_list.h"

void			ft_free_all(t_engine *engine);
int				ft_chk_lightrange(const double intensity);
int				ft_chk_dirrange(const t_vec3 dir);
int				ft_chk_colorrange(const t_color color);
int				ft_chk_fovrange(const int fov);

#endif
