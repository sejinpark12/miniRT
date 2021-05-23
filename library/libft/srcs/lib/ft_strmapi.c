/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 14:31:51 by sejpark           #+#    #+#             */
/*   Updated: 2021/05/23 18:28:20 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	int		i;

	if (s == NULL)
		return (NULL);
	result = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (result)
	{
		i = 0;
		while (s[i])
		{
			result[i] = f((unsigned int)i, s[i]);
			i++;
		}
		result[i] = '\0';
	}
	return (result);
}
