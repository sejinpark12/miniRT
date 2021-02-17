/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:59:14 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/17 22:07:10 by sejpark          ###   ########.fr       */
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

int		ft_hit_lst_hit(t_obj_lst *obj_lst, t_ray *r, t_t t, t_hit_rec *rec)
{
	t_hit_rec	tmp_rec;
	t_obj		*tmp;
	int			hit_anything;

	tmp = obj_lst->sp_world;
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
// 21.02.08 평면을 추가 하기 위해 코드추가
	tmp = obj_lst->pl_world;
	while (tmp)
	{
		if (ft_plane_hit(tmp->content, r, t, &tmp_rec))
		{
			hit_anything = 1;
			t.max = tmp_rec.t;
			*rec = tmp_rec;
		}
		tmp = tmp->next;
	}
//////////////////////////////////////////////////
	tmp = obj_lst->sq_world;
	while (tmp)
	{
		if (ft_square_hit(tmp->content, r, t, &tmp_rec))
		{
			hit_anything = 1;
			t.max = tmp_rec.t;
			*rec = tmp_rec;
		}
		tmp = tmp->next;
	}
	tmp = obj_lst->cy_world;
	while (tmp)
	{
		if (ft_cylinder_hit(tmp->content, r, t, &tmp_rec))
		{
			hit_anything = 1;
			t.max = tmp_rec.t;
			*rec = tmp_rec;
		}
		tmp = tmp->next;
	}
	return (hit_anything);
}
