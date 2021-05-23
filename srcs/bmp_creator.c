/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 17:44:30 by sejpark           #+#    #+#             */
/*   Updated: 2021/05/23 19:48:29 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bmp_creator.h"
#include <fcntl.h>
#include <unistd.h>

void	set_int_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

void	write_bmp_header(int fd, int filesize, t_engine *engine)
{
	int				i;
	int				tmp;
	unsigned char	bmpfileheader[54];

	i = 0;
	while (i < 54)
		bmpfileheader[i++] = (unsigned char)(0);
	bmpfileheader[0] = (unsigned char)('B');
	bmpfileheader[1] = (unsigned char)('M');
	set_int_in_char(bmpfileheader + 2, filesize);
	bmpfileheader[10] = (unsigned char)(54);
	bmpfileheader[14] = (unsigned char)(40);
	tmp = engine->data.width;
	set_int_in_char(bmpfileheader + 18, tmp);
	tmp = engine->data.height;
	set_int_in_char(bmpfileheader + 22, tmp);
	bmpfileheader[26] = (unsigned char)(1);
	bmpfileheader[28] = (unsigned char)(32);
	set_int_in_char(bmpfileheader + 38, 5000);
	set_int_in_char(bmpfileheader + 42, 5000);
	if (write(fd, bmpfileheader, 54) == -1)
	{
		close(fd);
		error_handler("bmp 파일 헤더 쓰기 실패", engine);
	}
}

void	bmp_pixel_data(int fd, t_engine *engine)
{
	int				i;
	int				j;
	unsigned int	color;
	t_data			*data;

	j = engine->data.height - 1;
	data = &(engine->data);
	while (j > -1)
	{
		i = 0;
		while (i < data->width)
		{
			color = *(unsigned int*)(((t_image*)(data->img_lst->content))->
			address + (j * data->line_length + i * (data->bits_per_pixel / 8)));
			if (write(fd, &color, 4) == -1)
			{
				close(fd);
				error_handler("bmp 파일 픽셀 데이터 쓰기 실패", engine);
			}
			i++;
		}
		j--;
	}
}

void	save_bmp(t_engine *engine)
{
	int	filesize;
	int	fd;

	filesize = 54 + (engine->data.width * engine->data.height) * 4;
	fd = open("screenshot.bmp", O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd == -1)
		error_handler("bmp 파일 생성 실패", engine);
	write_bmp_header(fd, filesize, engine);
	bmp_pixel_data(fd, engine);
	close(fd);
}
