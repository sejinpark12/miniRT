/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_reader.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:21:49 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/08 22:54:55 by sejpark          ###   ########.fr       */
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
typedef	struct	s_engine
{
	t_data		data;
	t_obj_lst	*cam_lst;
	t_obj_lst	*obj_lst;
	t_obj_lst	*light_lst;
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
typedef	struct	s_lights
{
	t_splight	*spli;
}				t_lights;
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
void			ft_free_all(t_engine *engine);
int				ft_chk_lightrange(const double intensity);
int				ft_chk_dirrange(const t_vec3 dir);
int				ft_chk_colorrange(const t_color color);
double			ft_beforepoint(const char *nbr, char **decimal_point,
								size_t *length);
double			ft_atof(const char *nbr);
int				ft_line_parser(t_engine *engine, char *line, int *r_chk, int *a_chk);
int				ft_scene_reader(t_engine *engine, char *filename);
int				ft_strcmp(const char *str1, const char *str2);
#endif
