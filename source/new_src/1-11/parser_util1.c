/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:28:01 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/10 20:35:29 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_util1.h"
#include <unistd.h>

void	ft_free_all(t_engine *engine)
{
	ft_hit_lst_clear(&(engine->cam_lst));
	ft_hit_lst_clear(&(engine->data.img_lst));
	ft_hit_lst_clear(&(engine->obj_lst));
	ft_hit_lst_clear(&(engine->light_lst));
	ft_par_lst_clear(&(engine->parser_lst));
	free(engine->data.fi.line);
	close(engine->data.fi.fd);
}

int		ft_chk_lightrange(const double intensity)
{
	if (intensity < 0 || intensity > 1)
		return (0);
	return (1);
}

int		ft_chk_dirrange(const t_vec3 dir)
{
	if (dir.x < -1 || dir.x > 1)
		return (0);
	if (dir.y < -1 || dir.y > 1)
		return (0);
	if (dir.z < -1 || dir.z > 1)
		return (0);
	return (1);
}

int		ft_chk_colorrange(const t_color color)
{
	if (color.x < 0 || color.x > 255)
		return (0);
	if (color.y < 0 || color.y > 255)
		return (0);
	if (color.z < 0 || color.z > 255)
		return (0);
	return (1);
}

int		ft_chk_fovrange(const int fov)
{
	if (fov < 0 || fov > 180)
		return (0);
	return (1);
}
