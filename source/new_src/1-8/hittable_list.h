/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable_list.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:47:39 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/17 22:05:41 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_LIST_H
# define HITTABLE_LIST_H
# include "hittable.h"
# include "sphere.h"
// 21.02.8 plane.h 추가
# include "plane.h"
# include "square.h"
# include "cylinder.h"
# include "libft/libft.h"

typedef t_list	t_obj;
// 21.02.08 sp, pl 리스트를 한번에 처리하기 까다로워서 일단 분리
typedef struct	s_obj_lst
{
	t_obj		*sp_world;
	t_obj		*pl_world;
	t_obj		*sq_world;
	t_obj		*cy_world;
}				t_obj_lst;
/////////////////////////////////////////////////////////////////////
void			ft_obj_del(void *node);
t_obj			*ft_hit_lst_newnode(void *newnode);
void			ft_hit_lst_add(t_obj **obj_lst, t_obj *node);
void			ft_hit_lst_delone(t_obj **obj_lst);
void			ft_hit_lst_clear(t_obj **obj_lst);
int				ft_hit_lst_hit(t_obj_lst *obj_lst, t_ray *r,
								t_t t, t_hit_rec *rec);

#endif
