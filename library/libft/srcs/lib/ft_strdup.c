/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 12:02:23 by sejpark           #+#    #+#             */
/*   Updated: 2021/05/23 18:28:20 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	strlen;
	char	*result;
	size_t	i;

	strlen = ft_strlen(s1);
	result = (char*)malloc((strlen + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	else
	{
		i = 0;
		while (i < strlen)
		{
			result[i] = s1[i];
			i++;
		}
		result[i] = '\0';
		return (result);
	}
}
