/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 12:02:23 by sejpark           #+#    #+#             */
/*   Updated: 2020/07/06 12:11:35 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
