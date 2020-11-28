/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:07:47 by sejpark           #+#    #+#             */
/*   Updated: 2020/11/24 18:07:16 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

unsigned short	g_lfsr = 0xACE1u;
unsigned int	g_bit;

unsigned int	my_rand(void)
{
	g_bit = ((g_lfsr >> 0) ^ (g_lfsr >> 2) ^ (g_lfsr >> 3) ^ (g_lfsr >> 5)) & 1;
	return (g_lfsr = (g_lfsr >> 1) | (g_bit << 15));
}

float			random_float(void)
{
    return (my_rand() / (MY_RAND_MAX + 1.0));
}

float			random_float_minmax(float min, float max)
{
    return (min + (max - min) * random_float());
}

float			ft_clamp(float x, float min, float max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}
