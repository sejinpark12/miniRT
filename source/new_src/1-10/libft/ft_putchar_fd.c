/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 15:36:13 by sejpark           #+#    #+#             */
/*   Updated: 2020/07/20 16:39:22 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	unsigned char uni;

	if ((unsigned char)c < 0x0080)
		write(fd, &c, 1);
	else
	{
		uni = (0b11000000 | (0b00011111 & ((unsigned char)c) >> 6));
		write(fd, &uni, 1);
		uni = (0b10000000 | (0b00111111 & ((unsigned char)c)));
		write(fd, &uni, 1);
	}
}
