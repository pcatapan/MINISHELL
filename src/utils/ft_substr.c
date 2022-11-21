/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 12:43:47 by pcatapan          #+#    #+#             */
/*   Updated: 2022/11/21 20:22:57 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Create a sub string
 * 
 * @param s 	String to create a sub string
 * @param start Index start to create a sub string
 * @param len 	Lengt of s
 * 
 * @return char*
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int		l;
	char				*str;
	unsigned int		i;

	if (!s)
		return (NULL);
	l = ft_strlen((char *)s);
	if (l < len)
		str = (char *)malloc(l * sizeof(char) + 1);
	else
		str = (char *)malloc(len * sizeof(char) + 1);
	i = 0;
	if (str == NULL)
		return (NULL);
	while (i <= l && len > 0 && start <= l)
	{
		str[i] = s[start];
		i++;
		start++;
		len--;
	}
	str[i] = '\0';
	return (str);
}
