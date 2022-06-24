/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:36:53 by pcatapan          #+#    #+#             */
/*   Updated: 2022/01/19 22:09:28 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	let;

	i = 0;
	let = c;
	while (s[i] != let && s[i] != '\0')
	{
		i++;
	}
	if (s[i] == let)
	{
		return ((char *)s + i);
	}
	return (NULL);
}
