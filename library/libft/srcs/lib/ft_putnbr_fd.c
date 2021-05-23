/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 16:26:51 by sejpark           #+#    #+#             */
/*   Updated: 2021/05/23 18:28:20 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_check_len_2(int n)
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

void	ft_putnbr_convert(char *nbr_str, int n)
{
	size_t			len;
	unsigned int	tmp_n;

	len = ft_check_len_2(n);
	nbr_str[len] = '\0';
	if (n == 0)
		nbr_str[0] = '0';
	else
	{
		if (n > 0)
			tmp_n = (unsigned int)n;
		else
		{
			nbr_str[0] = '-';
			tmp_n = n * -1;
		}
		while (tmp_n != 0)
		{
			nbr_str[--len] = (tmp_n % 10) + '0';
			tmp_n /= 10;
		}
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	char	nbr_str[12];

	i = 0;
	ft_putnbr_convert(nbr_str, n);
	while (nbr_str[i])
	{
		write(fd, &nbr_str[i], 1);
		i++;
	}
}
