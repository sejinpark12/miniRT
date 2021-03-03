/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:07:10 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/03 22:41:40 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"
#include <stdio.h>

void	my_mlx_pixel_put(t_data *data, t_image *img, int x, int y, t_vec3 *color)
{
    char    *dst;
	float	r;
	float	g;
	float	b;
	float	scale;

	scale = 1.0 / data->samples_per_pixel;
	r = color->x * scale;
	g = color->y * scale;
	b = color->z * scale;
    dst = img->address + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = create_trgb(0,
									256 * ft_clamp(r, 0.0, 0.999),
									256 * ft_clamp(g, 0.0, 0.999),
									256 * ft_clamp(b, 0.0, 0.999));
}

void	ft_window_close(t_engine *engine)
{
	ft_hit_lst_clear(&(engine->obj_lst));
	ft_hit_lst_clear(&(engine->light_lst));
	// 카메라 여러대 기능 추가하면 카메라도 메모리 해제 해야 한다.
	//ft_hit_lst_clear(&(engine->cam_lst));
	mlx_destroy_window(engine->data.mlx, engine->data.mlx_win);
	exit(0);
}

int		ft_key_press(int keycode, t_engine *engine)
{
	if (keycode == ESC)
		ft_window_close(engine);
	if (keycode == SPACEBAR)
	{
		if (engine->data.current_img_lst->next)
			engine->data.current_img_lst = engine->data.current_img_lst->next;
		else 
			engine->data.current_img_lst = engine->data.img_lst;
	}
	return (0);
}

int		ft_xbtn_click(t_engine *engine)
{
	ft_window_close(engine);
	return (0);
}

//int		ft_key_release(int keycode, t_data *data)
//{
//	return (0);
//}

t_color	ft_ray_color(t_ray *r, t_obj_lst *obj_lst, t_obj_lst *light_lst)
{
	t_color		color;
	float		t;
	t_hit_rec	rec;
	t_ray		sha_ray;
	t_t			t_minmax;
	t_spli_info spli_info;
	float		tmpcolor;
	int			vis;
	t_obj_lst	*cur_splight_lst;

	t_minmax.min = 0;
	t_minmax.max = FLT_MAX;
	if (ft_hit_lst_obj_hit(obj_lst, r, &t_minmax, &rec))
	{
		cur_splight_lst = light_lst;
		color = ft_vec_set_xyz(0, 0, 0);
		while(cur_splight_lst)
		{
			spli_info = ft_splight_get_info(cur_splight_lst->content, &rec.p);
			t_minmax.max = spli_info.distance;
			sha_ray = ft_ray_set(ft_vec_add(rec.p,
						ft_vec_mul_f(1e-4, rec.normal)),
						ft_vec_mul_f(-1, spli_info.lightdir));
			vis = (0 == ft_hit_lst_sha_hit(obj_lst, &sha_ray, &t_minmax)) ? 1 : 0;
			tmpcolor = ft_vec_dot(rec.normal,
						ft_vec_mul_f(-1, spli_info.lightdir));
			if (tmpcolor < 0)
				tmpcolor = 0;
			color.x += vis * rec.color.x * 0.18 / M_PI *
							spli_info.lightintensity.x * tmpcolor;
			color.y += vis * rec.color.y * 0.18 / M_PI *
							spli_info.lightintensity.y * tmpcolor;
			color.z += vis * rec.color.z * 0.18 / M_PI *
							spli_info.lightintensity.z * tmpcolor;
			cur_splight_lst = cur_splight_lst->next;
		}
		return (color);
	}
	t = 0.5 * (ft_vec_unit_vec(r->dir).y + 1.0);
	color = ft_vec_add(
				ft_vec_mul_f((1.0 - t), ft_vec_set_xyz(1.0, 1.0, 1.0)),
				ft_vec_mul_f(t, ft_vec_set_xyz(0.5, 0.7, 1.0)));
	return (color);
}

int		ft_draw(t_data *data, t_obj_lst *cam_lst, t_obj_lst *obj_lst,
							t_obj_lst *light_lst)
{
	int			i;
	int			j;
	int			k;
	t_vec3		color;
	t_ray		r;
	t_obj_lst	*tmp_img_lst;
	t_obj_lst	*tmp_cam_lst;

	tmp_img_lst = data->img_lst;
	tmp_cam_lst = cam_lst;
	while (tmp_img_lst)
	{
		j = data->height - 1;
		while (j >= 0)
		{
			i = 0;
			ft_putstr_fd("\rScanlines remaining: ", 1);
			ft_putnbr_fd(j, 1);
			ft_putchar_fd(' ', 1);
			while (i < data->width)
			{
				k = 0;
				color = ft_vec_set_xyz(0, 0, 0);
				while (k < data->samples_per_pixel)
				{
					r = ft_camera_get_ray(tmp_cam_lst->content,
								((float)i + ft_random_float()) / (data->width - 1),
								((float)j + ft_random_float()) / (data->height - 1));
					color = ft_vec_add(color, ft_ray_color(&r, obj_lst, light_lst));
					k++;
				}
				my_mlx_pixel_put(data, tmp_img_lst->content, i,
									data->height - 1 - j, &color);
				i++;
			}
			j--;
		}
		ft_putstr_fd("\n", 1);
		tmp_img_lst = tmp_img_lst->next;
		tmp_cam_lst = tmp_cam_lst->next;
	}
	//mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	return (0);
}

int		main_loop(t_engine *engine)
{
	t_image *img;

	img = engine->data.current_img_lst->content;
	mlx_put_image_to_window(engine->data.mlx, engine->data.mlx_win, img->image, 0, 0);
	return (0);
}
