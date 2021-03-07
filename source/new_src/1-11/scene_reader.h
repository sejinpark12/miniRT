/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_reader.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:21:49 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/07 21:04:41 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_READER_H
# define SCENE_READER_H
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include "renderer.h"

typedef	struct	s_cam_scene_data
{
	t_point3	viewpoint;
	t_vec3		dir;
	int			fov;
}				t_cam_scene_data;

#endif
