/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_reader.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:21:49 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/08 01:40:54 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_READER_H
# define SCENE_READER_H
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include "renderer.h"

typedef	struct	s_cam_scene_data
{
	t_point3	viewpoint;
	t_vec3		dir;
	int			fov;
}				t_cam_scene_data;
typedef	struct	s_light_scene_data
{
	t_point3	pos;
	double		intensity;
	t_color		color;
}				t_light_scene_data;
typedef struct	s_sphere_scene_data
{
	t_point3	center;
	double		diameter;
	t_color		color;
}				t_sphere_scene_data;
typedef	struct	s_plane_scene_data
{
	t_point3	center;
	t_vec3		norm;
	t_color		color;
}				t_plane_scene_data;
typedef struct	s_square_scene_data
{
	t_point3	center;
	t_vec3		norm;
	double		side_size;
	t_color		color;
}				t_square_scene_data;
typedef struct	s_cylinder_scene_data
{
	t_point3	center;
	t_vec3		dir;
	double		diameter;
	double		h;
	t_color		color;
}				t_cylinder_scene_data;
typedef	struct	s_triangle_scene_data
{
	t_point3	p0;
	t_point3	p1;
	t_point3	p2;
	t_color		color;
}				t_triangle_scene_data;
void			ft_line_parser(t_engine *engine, char *line);
int				ft_scene_reader(t_engine *engine, char *filename);
#endif
