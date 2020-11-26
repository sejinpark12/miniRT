/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:51:51 by sejpark           #+#    #+#             */
/*   Updated: 2020/11/20 19:54:12 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable_list.h"

void	ft_obj_del(void *node)
{
	free(((object*)node)->content);
}
object	*hit_lst_newnode(void *newnode)
{
	return (ft_lstnew(newnode));
}
void	hit_lst_add(object **obj_lst, object *node)
{
	ft_lstadd_back(obj_lst, node);
}
void	hit_lst_delone(object **obj_lst)
{
	ft_lstdelone(*obj_lst, ft_obj_del);
}
void	hit_lst_clear(object **obj_lst)
{
	ft_lstclear(obj_lst, ft_obj_del);
}
int		hit_lst_hit(object **obj_lst, const t_ray *r, float t_min, float t_max, t_hit_rec *rec)
{
	t_hit_rec	tmp_rec;
	object		*tmp;
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
