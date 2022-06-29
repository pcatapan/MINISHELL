/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 01:21:47 by pcatapan          #+#    #+#             */
/*   Updated: 2022/06/29 02:33:54 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Comparete two string
 * 
 * @param s1 string one
 * @param s2 string two
 * 
 * @return int 1 if the string is equal,
 * 0 if the string isn't equal
 */
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (s1[i] == s2[i])
	{
		i++;
		if (!s1[i] && !s2[i])
			return (1);
	}
	return (0);
}
