/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 12:24:04 by sejpark           #+#    #+#             */
/*   Updated: 2020/07/21 15:50:26 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*unchar_s1;
	unsigned char	*unchar_s2;

	i = 0;
	unchar_s1 = (unsigned char*)s1;
	unchar_s2 = (unsigned char*)s2;
	while (1)
	{
		if (i == n)
			break ;
		else if (unchar_s1[i] != unchar_s2[i])
			return (unchar_s1[i] - unchar_s2[i]);
		i++;
	}
	return (0);
}
