/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 20:16:09 by pcatapan          #+#    #+#             */
/*   Updated: 2022/06/26 20:18:04 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Concatenates two strings.
 *
 * @param dest The destination string.
 * @param src The source string.
 *
 * @returns The destination string.
 */
char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(dest);
	while (*(src + i))
	{
		*(dest + i + j) = *(src + i);
		i++;
	}
	*(dest + i + j) = '\0';
	return (dest);
}
