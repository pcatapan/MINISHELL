/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_searchstrchr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 01:37:46 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/02 20:41:39 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Search a n byte of str in all str of the array
 * 
 * @param str   str to find
 * @param array array in to search
 * 
 * @return char* sub str that eqaul to str less n byte
 */
char	*ft_searchstrchr(char const *str, char **array)
{
	int		i;
	int		len;
	char	*rtr;

	i = -1;
	len = ft_strlen((char *)str);
	while (array[++i])
	{
		if (ft_strncmp(str, array[i], len) == 0)
		{
			rtr = ft_substr(array[i], len, ft_strlen(array[i]));
			return (rtr);
		}
	}
	return (NULL);
}
