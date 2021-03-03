/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable_list1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:59:14 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/03 21:35:45 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable_list.h"

t_obj_lst	*ft_hit_lst_newobj(void *content, char obj_type)
{
	t_obj_lst *obj_lst;

	obj_lst = (t_obj_lst*)malloc(sizeof(t_obj_lst));
	if (obj_lst == NULL)
		return (NULL);
	else
	{
		obj_lst->obj_type = obj_type;
		obj_lst->content = content;
		obj_lst->next = NULL;
		return (obj_lst);
	}
}

t_obj_lst	*ft_hit_lst_last(t_obj_lst *obj_lst)
{
	if (obj_lst == NULL)
		return (NULL);
	while (obj_lst->next)
		obj_lst = obj_lst->next;
	return (obj_lst);
}

void	ft_hit_lst_addback(t_obj_lst **obj_lst, t_obj_lst *new_obj)
{
	t_obj_lst *cur;

	cur = *obj_lst;
	if (obj_lst == NULL)
		return ;
	if (*obj_lst == NULL)
		*obj_lst = new_obj;
	else
	{
		while (cur->next)
			cur = cur->next;
		cur->next = new_obj;
	}
}

void	ft_hit_lst_delone(t_obj_lst *obj_lst)
{
	free(obj_lst->content);
	free(obj_lst);
}

void	ft_hit_lst_clear(t_obj_lst **obj_lst)
{
	t_obj_lst *cur;
	t_obj_lst *tmp;

	cur = *obj_lst;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		ft_hit_lst_delone(tmp);
	}
	*obj_lst = NULL;
}
