/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:50:12 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/10 22:18:52 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

int	main(int argc, char **argv)
{
	t_engine	engine;

	engine.data.samples_per_pixel = 1;
	engine.obj_lst = NULL;
	engine.light_lst = NULL;
	engine.cam_lst = NULL;
	engine.parser_lst = NULL;
	engine.data.img_lst = NULL;
	engine.data.current_img_lst = NULL;
	engine.data.fi.line = NULL;
	if (argc < 2 || argc > 3)
		error_handler("main문의 인자수가 올바르지 않습니다.", &engine);
	ft_check_rtfile(argv[1], &engine);
	ft_scene_reader(&engine, argv[1]);
	if (engine.cam_lst == NULL)
		error_handler("camera가 존재하지 않아 장면을 생성할 수 없습니다.", &engine);
	if (engine.data.fi.r_chk == 0 || engine.data.fi.a_chk == 0)
		error_handler("resolution 또는 ambient가 존재하지 않습니다.", &engine);
	engine.data.mlx = mlx_init();
	ft_alloc_image(&engine);
	ft_draw(&engine.data, engine.cam_lst, engine.obj_lst, engine.light_lst);
	if (argc == 2)
		ft_create_window(&engine);
	else if (argc == 3 && ft_strcmp(argv[2], "--save") == 0)
	{
		ft_putstr_fd("--save 진입!", 1);
	}
	else
		error_handler("세 번째 인자가 올바르지 않습니다.", &engine);
	return (0);
}
