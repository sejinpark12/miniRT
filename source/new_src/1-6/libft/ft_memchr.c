/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 12:03:15 by sejpark           #+#    #+#             */
/*   Updated: 2020/07/01 12:30:09 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*unchar_s;

	i = 0;
	unchar_s = (unsigned char*)s;
	while (i < n)
	{
		if (unchar_s[i] == (unsigned char)c)
			return (&(unchar_s[i]));
		i++;
	}
	return (0);
}
