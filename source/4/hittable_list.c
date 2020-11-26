/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:51:51 by sejpark           #+#    #+#             */
/*   Updated: 2020/11/21 13:24:45 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable_list.h"

void		ft_obj_del(void *node)
{
	free(((t_object*)node)->content);
}

t_object	*hit_lst_newnode(void *newnode)
{
	return (ft_lstnew(newnode));
}

void		hit_lst_add(t_object **obj_lst, t_object *node)
{
	ft_lstadd_back(obj_lst, node);
}

void		hit_lst_delone(t_object **obj_lst)
{
	ft_lstdelone(*obj_lst, ft_obj_del);
}

void		hit_lst_clear(t_object **obj_lst)
{
	ft_lstclear(obj_lst, ft_obj_del);
}

int			hit_lst_hit(t_object **obj_lst, const t_ray *r, float t_min,
												float t_max, t_hit_rec *rec)
{
	t_hit_rec	tmp_rec;
	t_object	*tmp;
	int			hit_anything;
	float		closest_so_far;

	tmp = *obj_lst;
	hit_anything = 0;
	closest_so_far = t_max;
	while (tmp)
	{
		if (ft_sphere_hit(tmp->content, r, t_min, closest_so_far, &tmp_rec))
		{
			hit_anything = 1;
			closest_so_far = tmp_rec.t;
			*rec = tmp_rec;
		}
		tmp = tmp->next;
	}
	return (hit_anything);
}
