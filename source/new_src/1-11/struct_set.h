/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_set.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:31:36 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/10 12:19:36 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_SET_H
# define STRUCT_SET_H
# include "vec.h"
# include "hittable_list.h"
# include "parser_list.h"
# include "light.h"

typedef struct	s_ambient
{
	t_color		color;
	double		intensity;
}				t_ambient;
typedef struct	s_data
{
	void		*mlx;
	void		*mlx_win;
	double		aspect_ratio;
	int			width;
	int			height;
	t_ambient	ambient;
	int			x;
	int			y;
	int			z;
	int			samples_per_pixel;
	t_obj_lst	*img_lst;
	t_obj_lst	*current_img_lst;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;
typedef struct	s_engine
{
	t_data		data;
	t_obj_lst	*cam_lst;
	t_obj_lst	*obj_lst;
	t_obj_lst	*light_lst;
	t_par_lst	*parser_lst;
}				t_engine;
typedef struct	s_image
{
	void		*image;
	char		*address;
}				t_image;
typedef struct	s_imgs
{
	t_image		*img;
}				t_imgs;
typedef struct	s_cams
{
	t_camera	*cam;
}				t_cams;
typedef struct	s_objs
{
	t_sphere	*sp;
	t_plane		*pl;
	t_square	*sq;
	t_cylinder	*cy;
	t_triangle	*tr;
}				t_objs;
typedef struct	s_lights
{
	t_splight	*spli;
}				t_lights;

#endif
