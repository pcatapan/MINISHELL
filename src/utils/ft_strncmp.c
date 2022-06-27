/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 01:36:47 by pcatapan          #+#    #+#             */
/*   Updated: 2022/06/27 03:18:44 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Compares at most the first n bytes of s1 and s2.
 * 
 * @param s1 Frist string
 * @param s2 Second string
 * @param n bytes to confront
 * 
 * @return 0 then it indicates str1 is equal to str2.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && i < n && s1[i] && s2[i])
		i++;
	if (s1[i] != s2[i] && i < n)
		return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
	return (0);
}
