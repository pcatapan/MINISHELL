/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 01:38:25 by pcatapan          #+#    #+#             */
/*   Updated: 2022/06/26 20:57:17 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Concatenate two string
 * 
 * @param s1 string one
 * @param s2 string two
 * 
 * @return joined string
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*str;
	int			i;
	int			j;
	size_t		len;

	if (!s1 && !s2)
		return (NULL);
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	str = (char *)malloc(sizeof(char) * len);
	if (str == NULL)
		return (0);
	i = 0;
	j = 0;
	while (s1[j] != '\0')
	{
		str[j] = s1[j];
		j++;
	}
	while (s2[i] != '\0')
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}
