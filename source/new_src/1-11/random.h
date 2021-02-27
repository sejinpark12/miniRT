/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 21:10:25 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/27 17:26:11 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_H
# define RANDOM_H
# define FT_RAND_MAX	65535

unsigned int	ft_rand(void);
float			ft_random_float(void);
float			ft_random_float_range(float min, float max);
float			ft_clamp(float x, float min, float max);
#endif
