/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:59:14 by sejpark           #+#    #+#             */
/*   Updated: 2020/12/02 16:19:02 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable_list.h"

void	ft_obj_del(void *node)
{
	free(node);
}

t_obj	*ft_hit_lst_newnode(void *newnode)
{
	return (ft_lstnew(newnode));
}

void	ft_hit_lst_add(t_obj **obj_lst, t_obj *node)
{
	ft_lstadd_back(obj_lst, node);
}

void	ft_hit_lst_delone(t_obj **obj_lst)
{
	ft_lstdelone(*obj_lst, ft_obj_del);
}

void	ft_hit_lst_clear(t_obj **obj_lst)
{
	ft_lstclear(obj_lst, ft_obj_del);
}

int		ft_hit_lst_hit(t_obj **obj_lst, t_ray *r, t_t t, t_hit_rec *rec)
{
	t_hit_rec	tmp_rec;
	t_obj		*tmp;
	int			hit_anything;

	tmp = *obj_lst;
	hit_anything = 0;
	while (tmp)
	{
		if (ft_sphere_hit(tmp->content, r, t, &tmp_rec))
		{
			hit_anything = 1;
			t.max = tmp_rec.t;
			*rec = tmp_rec;
		}
		tmp = tmp->next;
	}
	return (hit_anything);
}
