/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable_list2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:41:20 by sejpark           #+#    #+#             */
/*   Updated: 2021/05/23 19:48:29 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hittable_list.h"

int	ft_hit_lst_obj_hit(t_obj_lst *obj_lst, t_ray *r, t_t *t_range,
						t_hit_rec *rec)
{
	int hit_anything;

	hit_anything = 0;
	while (obj_lst)
	{
		if (obj_lst->obj_type == 1
				&& ft_sphere_hit(obj_lst->content, r, t_range, rec))
			hit_anything = 1;
		else if (obj_lst->obj_type == 2
				&& ft_plane_hit(obj_lst->content, r, t_range, rec))
			hit_anything = 1;
		else if (obj_lst->obj_type == 3
				&& ft_square_hit(obj_lst->content, r, t_range, rec))
			hit_anything = 1;
		else if (obj_lst->obj_type == 4
				&& ft_cylinder_hit(obj_lst->content, r, t_range, rec))
			hit_anything = 1;
		else if (obj_lst->obj_type == 5
				&& ft_triangle_hit(obj_lst->content, r, t_range, rec))
			hit_anything = 1;
		obj_lst = obj_lst->next;
	}
	return (hit_anything);
}

int	ft_hit_lst_sha_hit(t_obj_lst *obj_lst, t_ray *r, t_t *t_range)
{
	while (obj_lst)
	{
		if (obj_lst->obj_type == 1
				&& ft_sphere_sha_hit(obj_lst->content, r, t_range))
			return (1);
		else if (obj_lst->obj_type == 2
				&& ft_plane_sha_hit(obj_lst->content, r, t_range))
			return (1);
		else if (obj_lst->obj_type == 3
				&& ft_square_sha_hit(obj_lst->content, r, t_range))
			return (1);
		else if (obj_lst->obj_type == 4
				&& ft_cylinder_sha_hit(obj_lst->content, r, t_range))
			return (1);
		else if (obj_lst->obj_type == 5
				&& ft_triangle_sha_hit(obj_lst->content, r, t_range))
			return (1);
		obj_lst = obj_lst->next;
	}
	return (0);
}
