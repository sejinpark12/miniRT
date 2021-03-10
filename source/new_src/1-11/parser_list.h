/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 12:08:28 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/10 12:39:04 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_LIST_H
# define PARSER_LIST_H
# include <stdlib.h>

typedef struct			s_par_lst
{
	char				**split_line;
	struct	s_par_lst	*next;
}						t_par_lst;
t_par_lst				*ft_par_lst_new(char **split_line);
void					ft_par_lst_addback(t_par_lst **par_lst,
							t_par_lst *new_par);
void					ft_par_lst_delone(t_par_lst *par_lst);
void					ft_par_lst_clear(t_par_lst **par_lst);
void					ft_free_split(char **split);

#endif
