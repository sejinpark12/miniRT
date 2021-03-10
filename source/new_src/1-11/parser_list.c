/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 12:07:53 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/10 22:17:45 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_list.h"

t_par_lst	*ft_par_lst_new(char **split_line)
{
	t_par_lst	*par_lst;

	par_lst = (t_par_lst*)malloc(sizeof(t_par_lst));
	if (par_lst == NULL)
		return (NULL);
	else
	{
		par_lst->split_line = split_line;
		par_lst->next = NULL;
		return (par_lst);
	}
}

void		ft_par_lst_addback(t_par_lst **par_lst, t_par_lst *new_par)
{
	t_par_lst	*cur;

	cur = *par_lst;
	if (par_lst == NULL)
		return ;
	if (*par_lst == NULL)
		*par_lst = new_par;
	else
	{
		while (cur->next)
			cur = cur->next;
		cur->next = new_par;
	}
}

void		ft_par_lst_delone(t_par_lst *par_lst)
{
	ft_free_split(par_lst->split_line);
	free(par_lst);
}

void		ft_par_lst_clear(t_par_lst **par_lst)
{
	t_par_lst	*cur;
	t_par_lst	*tmp;

	cur = *par_lst;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		ft_par_lst_delone(tmp);
	}
	*par_lst = NULL;
}

void		ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}
