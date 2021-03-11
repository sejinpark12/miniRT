/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_creator.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:42:41 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/11 21:01:29 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_CREATOR_H
# define BMP_CREATOR_H
# include "struct_set.h"
# include "error_handler.h"

void	set_int_in_char(unsigned char *start, int value);
void	write_bmp_header(int fd, int filesize, t_engine *engine);
void	bmp_pixel_data(int fd, t_engine *engine);
void	save_bmp(t_engine *engine);
#endif
