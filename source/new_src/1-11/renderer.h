/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:06:06 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/04 16:45:01 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft/libft.h"
#include "vec.h"
#include "ray.h"
#include "hittable_list.h"
#include "sphere.h"
#include "plane.h"
#include "square.h"
#include "cylinder.h"
#include "triangle.h"
#include "light.h"
#include "random.h"
#include "camera.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define ESC			53
#define SPACEBAR	49
#define X_BTN		17
#define KEYPRESS	2
#define KEYRELEASE	3

typedef struct 	s_data
{
	void		*mlx;
	void		*mlx_win;
	float		aspect_ratio;
	int			width;
	int			height;
	t_ambient	ambient;
	int			x;
	int			y;
	int			z;
	int			samples_per_pixel;
	t_obj_lst	*img_lst;
	t_obj_lst	*current_img_lst;
//	void		*img;
//	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;
typedef	struct	s_engine
{
	t_data		data;
	t_camera	*head_cam;
	t_obj_lst	*cam_lst;
	t_obj_lst	*obj_lst;
	t_obj_lst	*light_lst;
}				t_engine;
typedef struct	s_ambient
{
	t_color		color;
	float		intensity;
}				t_ambient;
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
void            my_mlx_pixel_put(t_data *data, t_image *img, int x, int y, t_vec3 *color);
void			ft_window_close(t_engine *engine);
int				ft_key_press(int keycode, t_engine *engine);
int				ft_xbtn_click(t_engine *engine);
//int				ft_key_release(int keycode, t_data *data);
t_color			ft_ray_color(t_ray *r, t_obj_lst *obj_lst,
							t_obj_lst *light_lst);
int				ft_draw(t_data *data, t_obj_lst *cam_lst, t_obj_lst *obj_lst,
							t_obj_lst *light_lst);
int				main_loop(t_engine *engine);
