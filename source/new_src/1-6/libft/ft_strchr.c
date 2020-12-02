/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 13:34:51 by sejpark           #+#    #+#             */
/*   Updated: 2020/07/04 17:51:21 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t i;
	size_t str_len;

	i = 0;
	str_len = ft_strlen(s);
	while (i < str_len + 1)
	{
		if (s[i] == (char)c)
			return ((char*)&s[i]);
		i++;
	}
	return (0);
}
