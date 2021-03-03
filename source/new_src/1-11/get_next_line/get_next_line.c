/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 12:03:10 by sejpark           #+#    #+#             */
/*   Updated: 2020/08/11 18:03:45 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define ERROR				-1
#define _EOF				 0
#define SUCCESS				 1
#define FULLBUF_NO_NEWLINE	 2
#define CANT_FIND_NEWLINE	-1

ssize_t	find_newline_char(const char *const str)
{
	int idx;

	idx = 0;
	while (str[idx])
	{
		if (str[idx] == '\n')
			return (idx);
		idx++;
	}
	return (CANT_FIND_NEWLINE);
}

int		make_static_buf(int fd, char *const buf, ssize_t *const read_cnt,
		char **static_buf)
{
	char *tmp;

	if (ERROR == (*read_cnt = read(fd, buf, BUFFER_SIZE)))
		return (ERROR);
	buf[*read_cnt] = '\0';
	if (*static_buf)
	{
		tmp = *static_buf;
		*static_buf = ft_strjoin(*static_buf, buf);
		free(tmp);
		if (NULL == *static_buf)
			return (ERROR);
	}
	else if (NULL == (*static_buf = ft_strdup(buf)))
		return (ERROR);
	return (SUCCESS);
}

int		meet_eof(char **const line, char **static_buf)
{
	*line = ft_strdup(*static_buf);
	free(*static_buf);
	*static_buf = NULL;
	if (*line == NULL)
		return (ERROR);
	return (_EOF);
}

int		get_line(ssize_t *const read_cnt, char **const line,
		char **static_buf)
{
	int		newline_idx;
	char	*tmp;

	newline_idx = find_newline_char(*static_buf);
	if (newline_idx == CANT_FIND_NEWLINE && *read_cnt)
		return (FULLBUF_NO_NEWLINE);
	if (*read_cnt == 0 && newline_idx == CANT_FIND_NEWLINE)
		return (meet_eof(line, static_buf));
	tmp = *static_buf;
	(*static_buf)[newline_idx] = '\0';
	*line = ft_strdup(*static_buf);
	*static_buf = ft_strdup(*static_buf + newline_idx + 1);
	free(tmp);
	if (*line == NULL || *static_buf == NULL)
	{
		free(*line);
		free(*static_buf);
		*static_buf = NULL;
		return (ERROR);
	}
	return (SUCCESS);
}

int		get_next_line(int fd, char **line)
{
	char		*buf;
	static char *static_buf = NULL;
	ssize_t		read_cnt;
	int			result;

	read_cnt = -1;
	result = -1;
	if (NULL == (buf = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (ERROR);
	while ((fd > -1 && fd <= OPEN_MAX) && BUFFER_SIZE > 0 && line)
	{
		if (ERROR == make_static_buf(fd, buf, &read_cnt, &static_buf))
			break ;
		if (ERROR == (result = get_line(&read_cnt, line, &static_buf)))
			break ;
		if (FULLBUF_NO_NEWLINE == result)
			continue ;
		free(buf);
		return (result);
	}
	free(buf);
	return (ERROR);
}
