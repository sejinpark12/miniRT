/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:50:12 by sejpark           #+#    #+#             */
/*   Updated: 2021/05/23 19:48:29 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/renderer.h"
#include "../includes/bmp_creator.h"

int	main(int argc, char **argv)
{
	t_engine	engine;

	ft_engine_init(&engine);
	if (argc < 2 || argc > 3)
		error_handler("main문의 인자수가 올바르지 않습니다.", &engine);
	ft_check_rtfile(argv[1], &engine);
	ft_scene_reader(&engine, argv[1]);
	if (engine.cam_lst == NULL)
		error_handler("cam이 존재하지 않아 씬을 생성할 수 없습니다.", &engine);
	if (engine.data.fi.r_chk == 0 || engine.data.fi.a_chk == 0)
		error_handler("resolution 또는 ambient가 존재하지 않습니다.", &engine);
	if (argc == 3 && ft_strcmp(argv[2], "--save") != 0)
		error_handler("세 번째 인자가 올바르지 않습니다.", &engine);
	engine.data.mlx = mlx_init();
	if (engine.data.mlx == NULL)
		error_handler("mlx_init 실패", &engine);
	ft_alloc_image(&engine);
	ft_draw(&engine);
	if (argc == 2)
		ft_create_window(&engine);
	else if (argc == 3 && ft_strcmp(argv[2], "--save") == 0)
		save_bmp(&engine);
	else
		error_handler("세 번째 인자가 올바르지 않습니다.", &engine);
	return (0);
}
