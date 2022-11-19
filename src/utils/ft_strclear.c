/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 00:31:42 by pcatapan          #+#    #+#             */
/*   Updated: 2022/11/13 01:08:36 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Delete the del in str
 * 
 * @param str String to delete from
 * @param del Character to delete
 * @return char* 
 */
char	*ft_strclear(char *str, char del)
{
	int		i;
	int		count;
	char	*rtr;

	i = -1;
	while (str[++i])
	{
		if (str[i] != del)
			count++;
	}
	rtr = (char *)malloc(sizeof(char) * count);
	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] != del)
			rtr[count++] = str[i];
	}
	if (rtr)
	{
		rtr[count++] = '\0';
		return (rtr);
	}
	return (NULL);
}
