/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:06:06 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/08 17:25:48 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H
# define ESC		53
# define SPACEBAR	49
# define X_BTN		17
# define KEYPRESS	2
# define KEYRELEASE	3
# include "mlx.h"
# include "libft/libft.h"
# include "scene_reader.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <float.h>

void			my_mlx_pixel_put(t_data *data, t_image *img, int x, int y,
						t_vec3 *color);
void			ft_window_close(t_engine *engine);
int				ft_key_press(int keycode, t_engine *engine);
int				ft_xbtn_click(t_engine *engine);
t_color			ft_ray_color(t_ray *r, t_obj_lst *obj_lst,
							t_obj_lst *light_lst);
int				ft_draw(t_data *data, t_obj_lst *cam_lst, t_obj_lst *obj_lst,
							t_obj_lst *light_lst);
int				main_loop(t_engine *engine);
int				ft_check_rtfile(const char *filename);
#endif
