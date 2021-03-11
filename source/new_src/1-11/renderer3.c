/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:21:15 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/11 17:21:48 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

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
