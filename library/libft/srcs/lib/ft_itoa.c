/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 12:58:34 by sejpark           #+#    #+#             */
/*   Updated: 2021/05/23 18:28:20 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t		ft_check_len(int n)
{
	size_t			len;
	unsigned int	tmp_n;

	len = 0;
	if (n > 0)
	{
		len = 0;
		tmp_n = (unsigned int)n;
	}
	else if (n < 0)
	{
		len = 1;
		tmp_n = n * -1;
	}
	else
		return (1);
	while (tmp_n != 0)
	{
		tmp_n /= 10;
		len++;
	}
	return (len);
}

char		*ft_convert(size_t len, int n)
{
	char			*result;
	unsigned int	tmp_n;

	result = (char*)malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	result[len] = '\0';
	if (n == 0)
		result[0] = '0';
	else
	{
		if (n > 0)
			tmp_n = (unsigned int)n;
		else
		{
			result[0] = '-';
			tmp_n = n * -1;
		}
		while (tmp_n != 0)
		{
			result[--len] = (tmp_n % 10) + '0';
			tmp_n /= 10;
		}
	}
	return (result);
}

char		*ft_itoa(int n)
{
	size_t	len;
	char	*result;

	len = ft_check_len(n);
	result = ft_convert(len, n);
	return (result);
}
