/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 20:02:56 by sejpark           #+#    #+#             */
/*   Updated: 2021/05/23 18:31:01 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	int		i;
	t_list	*begin;
	t_list	*ele;

	i = 0;
	begin = NULL;
	ele = NULL;
	while (lst)
	{
		ele = ft_lstnew(f(lst->content));
		if (ele == NULL)
		{
			ft_lstclear(&begin, del);
			return (NULL);
		}
		ft_lstadd_back(&begin, ele);
		i++;
		lst = lst->next;
	}
	return (begin);
}
