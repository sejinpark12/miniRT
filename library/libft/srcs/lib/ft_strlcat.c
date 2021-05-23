/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 13:21:29 by sejpark           #+#    #+#             */
/*   Updated: 2021/05/23 18:28:20 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src,
					size_t dstsize)
{
	size_t i;
	size_t before_dst_len;
	size_t cnt;

	i = 0;
	before_dst_len = ft_strlen(dst);
	cnt = dstsize - before_dst_len - 1;
	if (before_dst_len >= dstsize)
	{
		return (dstsize + ft_strlen(src));
	}
	else
	{
		while (i < cnt)
		{
			if (src[i] == '\0')
				break ;
			dst[before_dst_len + i] = src[i];
			i++;
		}
		dst[before_dst_len + i] = '\0';
	}
	return (before_dst_len + ft_strlen(src));
}
