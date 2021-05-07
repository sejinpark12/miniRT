/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 21:10:25 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/05 16:12:50 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_H
# define RANDOM_H
# define FT_RAND_MAX	65535

unsigned int	ft_rand(void);
double			ft_random_double(void);
double			ft_random_double_range(double min, double max);
double			ft_clamp(double x, double min, double max);
#endif
