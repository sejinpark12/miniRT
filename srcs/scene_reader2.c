/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_reader2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:29:14 by sejpark           #+#    #+#             */
/*   Updated: 2021/05/23 19:48:29 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scene_reader.h"

void	ft_scene_reader(t_engine *engine, char *filename)
{
	ft_file_set(filename, engine);
	while (engine->data.fi.ret > 0)
	{
		if (ft_strcmp(engine->data.fi.line, "") != 0)
			ft_line_parser(engine, engine->data.fi.line,
					&(engine->data.fi.r_chk), &(engine->data.fi.a_chk));
		free(engine->data.fi.line);
		engine->data.fi.ret = get_next_line(engine->data.fi.fd,
				&(engine->data.fi.line));
		if (engine->data.fi.ret == -1)
			error_handler("get_next_line 오류", engine);
	}
	if (ft_strcmp(engine->data.fi.line, "") != 0)
		ft_line_parser(engine, engine->data.fi.line, &(engine->data.fi.r_chk),
				&(engine->data.fi.a_chk));
	free(engine->data.fi.line);
	engine->data.fi.line = NULL;
	ft_par_lst_clear(&(engine->parser_lst));
	engine->parser_lst = NULL;
	close(engine->data.fi.fd);
}
