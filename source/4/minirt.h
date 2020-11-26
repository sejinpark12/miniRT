/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 17:58:01 by sejpark           #+#    #+#             */
/*   Updated: 2020/11/24 18:06:05 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include "mlx/mlx.h"
# include "libft/libft.h"
# include "ray.h"
# include "vec3.h"
# define MY_RAND_MAX 65535

typedef struct	s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;
unsigned int	my_rand(void);
float			random_float(void);
float			random_float_minmax(float min, float max);
float			ft_clamp(float x, float min, float max);
#endif

