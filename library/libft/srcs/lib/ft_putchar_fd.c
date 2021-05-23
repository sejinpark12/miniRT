/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 15:36:13 by sejpark           #+#    #+#             */
/*   Updated: 2021/05/23 18:28:20 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

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
