/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:26:12 by sejpark           #+#    #+#             */
/*   Updated: 2021/05/23 19:54:21 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTIL_H
# define PARSER_UTIL_H
# include "struct_set.h"
# include "vec.h"
# include "hittable_list.h"
# include "../library/libft/includes/libft.h"
# include "error_handler.h"

void	ft_free_all(t_engine *engine);
int		ft_chk_lightrange(const double intensity);
int		ft_chk_dirrange(const t_vec3 dir);
int		ft_chk_colorrange(const t_color color);
int		ft_chk_fovrange(const int fov);
int		ft_strcmp(const char *str1, const char *str2);
double	ft_beforepoint(const char *nbr, char **decimal_point, int *length,
			t_engine *engine);
double	ft_atof(const char *nbr, t_engine *engine);
int		ft_atoi_minirt(char *str, t_engine *engine);
int		ft_count_split(char **split_line);
char	**ft_get_split_data(t_engine *engine, char *str, char separator,
			int cnt);
void	ft_add_split_data_to_par_lst(t_engine *engine, char **split_line);
#endif
