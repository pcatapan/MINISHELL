/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:05:33 by pcatapan          #+#    #+#             */
/*   Updated: 2022/01/17 18:47:38 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t destsize)
{
	size_t	i;
	size_t	j;
	size_t	x;

	i = ft_strlen(dst);
	j = ft_strlen((char *)src);
	x = 0;
	if (destsize <= i)
		x = j + destsize;
	else
		x = j + i;
	j = 0;
	while (src[j] != '\0' && i + 1 < destsize)
		dst[i++] = src[j++];
	if (j > 0)
		dst[i] = '\0';
	return (x);
}
