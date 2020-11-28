/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable_list.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:47:43 by sejpark           #+#    #+#             */
/*   Updated: 2020/11/21 13:23:25 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_LIST_H
# define HITTABLE_LIST_H
# include "hittable.h"
# include "sphere.h"
# include "libft/libft.h"

typedef t_list	t_object;
void			ft_obj_del(void *node);
t_object		*hit_lst_newnode(void *newnode);
void			hit_lst_add(t_object **obj_lst, t_object *node);
void			hit_lst_delone(t_object **obj_lst);
void			hit_lst_clear(t_object **obj_lst);
int				hit_lst_hit(
							t_object	**obj_lst,
							const t_ray *r,
							float		t_min,
							float		t_max,
							t_hit_rec	*rec);
#endif
