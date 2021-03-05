/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable_list.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:47:39 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/05 14:43:07 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_LIST_H
# define HITTABLE_LIST_H
# include "hittable.h"
# include "camera.h"
# include "sphere.h"
# include "plane.h"
# include "square.h"
# include "cylinder.h"
# include "triangle.h"
# include <stdlib.h>

typedef	struct			s_obj_lst
{
	char				obj_type;
	void				*content;
	struct s_obj_lst	*next;
}						t_obj_lst;
t_obj_lst				*ft_hit_lst_newobj(void *content, char obj_type);
t_obj_lst				*ft_hit_lst_last(t_obj_lst *obj_lst);
void					ft_hit_lst_addback(t_obj_lst **obj_lst,
									t_obj_lst *new_obj);
void					ft_hit_lst_delone(t_obj_lst *obj_lst);
void					ft_hit_lst_clear(t_obj_lst **obj_lst);
int						ft_hit_lst_obj_hit(t_obj_lst *obj_lst, t_ray *r,
								t_t *t_range, t_hit_rec *rec);
int						ft_hit_lst_sha_hit(t_obj_lst *obj_lst, t_ray *r,
								t_t *t_range);
#endif
