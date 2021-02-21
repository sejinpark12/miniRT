/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 21:15:37 by sejpark           #+#    #+#             */
/*   Updated: 2020/12/05 23:32:22 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_random.h"

unsigned short	g_lfsr = 0xACE1u;
unsigned int	g_bit;

unsigned int	ft_rand(void)
{
	g_bit = ((g_lfsr >> 0) ^ (g_lfsr >> 2) ^ (g_lfsr >> 3) ^ (g_lfsr >> 5))
																		& 1;
	return (g_lfsr = (g_lfsr >> 1) | (g_bit << 15));
}

float			ft_random_float(void)
{
	return (ft_rand() / (FT_RAND_MAX + 1.0));
}

float			ft_random_float_range(float min, float max)
{
	return (min + (max - min) * ft_random_float());
}

float			ft_clamp(float x, float min, float max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}
