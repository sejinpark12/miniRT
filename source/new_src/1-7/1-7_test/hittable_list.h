/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable_list.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:47:39 by sejpark           #+#    #+#             */
/*   Updated: 2020/12/02 15:59:08 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_LIST_H
# define HITTABLE_LIST_H
# include "hittable.h"
# include "sphere.h"
# include "libft/libft.h"

typedef t_list	t_obj;
void			ft_obj_del(void *node);
t_obj			*ft_hit_lst_newnode(void *newnode);
void			ft_hit_lst_add(t_obj **obj_lst, t_obj *node);
void			ft_hit_lst_delone(t_obj **obj_lst);
void			ft_hit_lst_clear(t_obj **obj_lst);
int				ft_hit_lst_hit(t_obj **obj_lst, t_ray *r,
														t_t t, t_hit_rec *rec);

#endif
