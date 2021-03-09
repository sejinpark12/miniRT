/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:50:12 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/09 03:07:15 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

int	main(int argc, char **argv)
{
	t_engine	engine;
	t_imgs		imgs;
	t_obj_lst	*tmp_cam_lst;

	// Image
	engine.data.samples_per_pixel = 1;
	// World
	engine.obj_lst = NULL;
	// light
	engine.light_lst = NULL;
	// camera
	engine.cam_lst = NULL;
	// image
	engine.data.img_lst = NULL;
	engine.data.current_img_lst = NULL;
	// scene_read
	if (argc < 2 || argc > 3)
	{
		ft_putstr_fd("Error\n", 1);
		exit(0);
		// 에러!!!
	}
	else if (ft_check_rtfile(argv[1]))
	{
		printf("ft_check_rtfile in!!!\n");
		if (ft_scene_reader(&engine, argv[1]) == -1 || engine.cam_lst == NULL)
		{
			ft_putstr_fd("Error\n", 1);
			ft_free_all(&engine);
			exit(0);
			// 에러 !!
		}
		engine.data.mlx = mlx_init();
		tmp_cam_lst = engine.cam_lst;
		while (tmp_cam_lst)
		{
			imgs.img = (t_image*)malloc(sizeof(t_image));
			imgs.img->image = mlx_new_image(engine.data.mlx, engine.data.width,
									engine.data.height);
			imgs.img->address = mlx_get_data_addr(imgs.img->image,
							&engine.data.bits_per_pixel,
							&engine.data.line_length, &engine.data.endian);
			ft_hit_lst_addback(&engine.data.img_lst,
								ft_hit_lst_newobj(imgs.img, 30));
			tmp_cam_lst = tmp_cam_lst->next;
		}
		engine.data.current_img_lst = engine.data.img_lst;
		ft_draw(&engine.data, engine.cam_lst, engine.obj_lst, engine.light_lst);
		if (argc == 2)
		{
			// Render
			engine.data.mlx_win = mlx_new_window(
										engine.data.mlx, engine.data.width,
										engine.data.height, "miniRT");
			mlx_loop_hook(engine.data.mlx, main_loop, &engine);
			mlx_hook(engine.data.mlx_win, KEYPRESS, 1L<<0, ft_key_press, &engine);
			mlx_hook(engine.data.mlx_win, X_BTN, 1L<<0, ft_xbtn_click, &engine);
			mlx_loop(engine.data.mlx);
		}
		else if (argc == 3 &&
					ft_strncmp(argv[2], "--save", ft_strlen(argv[2])) == 0)
		{

		}
		else
		{
			ft_putstr_fd("Error\n", 1);
			ft_free_all(&engine);
			exit(0);
			// 에러 !!
		}
	}
	else
	{
		ft_putstr_fd("Error\n", 1);
		exit(0);
		// 에러 !!
	}
	return (0);
}
