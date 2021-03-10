/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:07:10 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/10 22:35:03 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

void	my_mlx_pixel_put(t_data *data, t_image *img, t_pixel p,
							t_vec3 *color)
{
	char	*dst;
	double	r;
	double	g;
	double	b;
	double	scale;

	scale = 1.0 / data->samples_per_pixel;
	r = color->x * scale;
	g = color->y * scale;
	b = color->z * scale;
	dst = img->address +
				(p.y * data->line_length + p.x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = create_trgb(0,
									ft_clamp(r, 0, 255),
									ft_clamp(g, 0, 255),
									ft_clamp(b, 0, 255));
}

void	ft_window_close(t_engine *engine)
{
	ft_free_all(engine);
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

t_color	ft_ray_color(t_ray *r, t_obj_lst *obj_lst, t_obj_lst *light_lst,
						t_ambient ambient)
{
	t_color		color;
	double		t;
	t_hit_rec	rec;
	t_ray		sha_ray;
	t_t			t_minmax;
	t_spli_info spli_info;
	double		tmpcolor;
	int			vis;
	t_obj_lst	*cur_splight_lst;

	t_minmax.min = 0;
	t_minmax.max = DBL_MAX;
	if (ft_hit_lst_obj_hit(obj_lst, r, &t_minmax, &rec))
	{
		cur_splight_lst = light_lst;
		color = ft_vec_mul_f(0.001 * ambient.intensity,
							ft_vec_mul(rec.color, ambient.color));
		while (cur_splight_lst)
		{
			spli_info = ft_splight_get_info(cur_splight_lst->content, &rec.p);
			t_minmax.max = spli_info.distance;
			sha_ray = ft_ray_set(ft_vec_add(rec.p,
						ft_vec_mul_f(1e-4, rec.normal)),
						ft_vec_mul_f(-1, spli_info.lightdir));
			vis = (0 == ft_hit_lst_sha_hit(obj_lst, &sha_ray, &t_minmax))
					? 1 : 0;
			tmpcolor = ft_vec_dot(rec.normal,
						ft_vec_mul_f(-1, spli_info.lightdir));
			if (tmpcolor < 0)
				tmpcolor = 0;
			color.x += vis * rec.color.x * 0.18 / M_PI *
							spli_info.lightintensity.x * 5000 * tmpcolor;
			color.y += vis * rec.color.y * 0.18 / M_PI *
							spli_info.lightintensity.y * 5000 * tmpcolor;
			color.z += vis * rec.color.z * 0.18 / M_PI *
							spli_info.lightintensity.z * 5000 * tmpcolor;
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

void	ft_alloc_image(t_engine *engine)
{
	t_imgs		imgs;
	t_obj_lst	*tmp_cam_lst;
	t_obj_lst	*new_cam_lst;

	tmp_cam_lst = engine->cam_lst;
	while (tmp_cam_lst)
	{
		imgs.img = (t_image*)malloc(sizeof(t_image));
		if (imgs.img == NULL)
			error_handler("image 메모리 동적할당 실패", engine);
		imgs.img->image = mlx_new_image(engine->data.mlx, engine->data.width,
								engine->data.height);
		imgs.img->address = mlx_get_data_addr(imgs.img->image,
						&engine->data.bits_per_pixel,
						&engine->data.line_length, &engine->data.endian);
		new_cam_lst = ft_hit_lst_newobj(imgs.img, 30);
		if (new_cam_lst == NULL)
			error_handler("ft_hit_lst_newobj 메모리 동적할당 실패", engine);
		ft_hit_lst_addback(&engine->data.img_lst, new_cam_lst);
		tmp_cam_lst = tmp_cam_lst->next;
	}
	engine->data.current_img_lst = engine->data.img_lst;
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
	int			cam_idx;
	t_pixel		p;

	tmp_img_lst = data->img_lst;
	tmp_cam_lst = cam_lst;
	cam_idx = 1;
	ft_putstr_fd("*********** Rendering... ***********\n", 1);
	while (tmp_img_lst)
	{
		j = data->height - 1;
		while (j >= 0)
		{
			i = 0;
			ft_putstr_fd("\r Cam ", 1);
			ft_putnbr_fd(cam_idx, 1);
			ft_putstr_fd(" => Scanlines remaining: ", 1);
			ft_putnbr_fd(j, 1);
			ft_putchar_fd(' ', 1);
			while (i < data->width)
			{
				k = 0;
				color = ft_vec_set_xyz(0, 0, 0);
				while (k < data->samples_per_pixel)
				{
					r = ft_camera_get_ray(tmp_cam_lst->content,
						((double)i + ft_random_double()) / (data->width - 1),
						((double)j + ft_random_double()) / (data->height - 1));
					color = ft_vec_add(color,
							ft_ray_color(&r, obj_lst, light_lst, data->ambient));
					k++;
				}
				p.x = i;
				p.y = data->height - 1 - j;
				my_mlx_pixel_put(data, tmp_img_lst->content, p, &color);
				i++;
			}
			j--;
		}
		ft_putstr_fd("\n", 1);
		tmp_img_lst = tmp_img_lst->next;
		tmp_cam_lst = tmp_cam_lst->next;
		cam_idx++;
	}
	ft_putstr_fd("************************************\n", 1);
	ft_putstr_fd("Done!\n", 1);
	return (0);
}

void	ft_create_window(t_engine *engine)
{
	engine->data.mlx_win = mlx_new_window(
								engine->data.mlx, engine->data.width,
								engine->data.height, "miniRT");
	if (engine->data.mlx_win == NULL)
		error_handler("mlx_new_window 실패", engine);
	mlx_loop_hook(engine->data.mlx, main_loop, engine);
	mlx_hook(engine->data.mlx_win, KEYPRESS, 0, ft_key_press, engine);
	mlx_hook(engine->data.mlx_win, X_BTN, 0, ft_xbtn_click, engine);
	mlx_loop(engine->data.mlx);
}

int		main_loop(t_engine *engine)
{
	t_image *img;

	img = engine->data.current_img_lst->content;
	mlx_put_image_to_window(engine->data.mlx, engine->data.mlx_win,
								img->image, 0, 0);
	return (0);
}
