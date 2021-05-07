/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:49:20 by sejpark           #+#    #+#             */
/*   Updated: 2021/05/07 15:50:23 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

t_color	ft_calculate_color(t_obj_lst **cur_splight_lst, t_hit_rec *rec,
			t_t *t_minmax, t_obj_lst *obj_lst)
{
	t_color		color;
	t_spli_info	spli_info;
	t_ray		sha_ray;
	double		tmpcolor;
	int			vis;

	spli_info = ft_splight_get_info((*cur_splight_lst)->content, &rec->p);
	t_minmax->max = spli_info.distance;
	sha_ray = ft_ray_set(ft_vec_add(rec->p,
				ft_vec_mul_f(1e-4, rec->normal)),
				ft_vec_mul_f(-1, spli_info.lightdir));
	vis = (0 == ft_hit_lst_sha_hit(obj_lst, &sha_ray, t_minmax)) ? 1 : 0;
	tmpcolor = ft_vec_dot(rec->normal, ft_vec_mul_f(-1, spli_info.lightdir));
	if (tmpcolor < 0)
		tmpcolor = 0;
	color.x = vis * rec->color.x * 0.18 / M_PI *
					spli_info.lightintensity.x * 5000 * tmpcolor;
	color.y = vis * rec->color.y * 0.18 / M_PI *
					spli_info.lightintensity.y * 5000 * tmpcolor;
	color.z = vis * rec->color.z * 0.18 / M_PI *
					spli_info.lightintensity.z * 5000 * tmpcolor;
	*cur_splight_lst = (*cur_splight_lst)->next;
	return (color);
}

t_color	ft_ray_color(t_ray *r, t_engine *engine)
{
	t_color		color;
	t_color		tmp_color;
	t_hit_rec	rec;
	t_t			t_minmax;
	t_obj_lst	*cur_splight_lst;

	t_minmax.min = 0;
	t_minmax.max = DBL_MAX;
	if (ft_hit_lst_obj_hit(engine->obj_lst, r, &t_minmax, &rec))
	{
		cur_splight_lst = engine->light_lst;
		color = ft_vec_mul_f(0.001 * engine->data.ambient.intensity,
							ft_vec_mul(rec.color, engine->data.ambient.color));
		while (cur_splight_lst)
		{
			tmp_color = ft_calculate_color(&cur_splight_lst, &rec, &t_minmax,
							engine->obj_lst);
			color = ft_vec_add(color, tmp_color);
		}
		return (color);
	}
	color = ft_vec_set_xyz(0, 0, 0);
	return (color);
}

void	ft_calculate_image(t_engine *engine, t_obj_lst **tmp_img_lst,
			t_obj_lst **tmp_cam_lst, int j)
{
	int			i;
	int			k;
	t_vec3		color;
	t_ray		r;
	t_pixel		p;

	i = 0;
	while (i < engine->data.width)
	{
		k = 0;
		color = ft_vec_set_xyz(0, 0, 0);
		while (k < engine->data.samples_per_pixel)
		{
			r = ft_camera_get_ray((*tmp_cam_lst)->content,
			((double)i + ft_random_double()) / (engine->data.width - 1),
			((double)j + ft_random_double()) / (engine->data.height - 1));
			color = ft_vec_add(color, ft_ray_color(&r, engine));
			k++;
		}
		p.x = i;
		p.y = engine->data.height - 1 - j;
		my_mlx_pixel_put(&engine->data, (*tmp_img_lst)->content, p, &color);
		i++;
	}
}

void	ft_print_scanlines(int cam_idx, int j)
{
	ft_putstr_fd("\r Cam ", 1);
	ft_putnbr_fd(cam_idx, 1);
	ft_putstr_fd(" => Scanlines remaining: ", 1);
	ft_putnbr_fd(j, 1);
	ft_putchar_fd(' ', 1);
}

int		ft_draw(t_engine *engine)
{
	int			j;
	t_obj_lst	*tmp_img_lst;
	t_obj_lst	*tmp_cam_lst;
	int			cam_idx;

	tmp_img_lst = engine->data.img_lst;
	tmp_cam_lst = engine->cam_lst;
	cam_idx = 1;
	ft_putstr_fd("*********** RENDERING... ***********\n", 1);
	while (tmp_img_lst)
	{
		j = engine->data.height - 1;
		while (j >= 0)
		{
			ft_print_scanlines(cam_idx, j);
			ft_calculate_image(engine, &tmp_img_lst, &tmp_cam_lst, j);
			j--;
		}
		ft_putstr_fd("\n", 1);
		tmp_img_lst = tmp_img_lst->next;
		tmp_cam_lst = tmp_cam_lst->next;
		cam_idx++;
	}
	ft_putstr_fd("************************************\nDONE!\n", 1);
	if (cam_idx > 2)
		ft_putstr_fd("Cam Switching : Press Space Bar\n", 1);
	return (0);
}
