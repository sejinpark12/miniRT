/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:07:10 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/12 10:36:19 by sejpark          ###   ########.fr       */
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

void	ft_create_window(t_engine *engine)
{
	t_image *img;

	engine->data.mlx_win = mlx_new_window(
								engine->data.mlx, engine->data.width,
								engine->data.height, "miniRT");
	if (engine->data.mlx_win == NULL)
		error_handler("mlx_new_window 실패", engine);
	img = engine->data.current_img_lst->content;
	mlx_put_image_to_window(engine->data.mlx, engine->data.mlx_win,
								img->image, 0, 0);
	mlx_hook(engine->data.mlx_win, KEYPRESS, 0, ft_key_press, engine);
	mlx_hook(engine->data.mlx_win, X_BTN, 0, ft_xbtn_click, engine);
	mlx_loop(engine->data.mlx);
}
