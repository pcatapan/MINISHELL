/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_searchstrchr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 01:37:46 by pcatapan          #+#    #+#             */
/*   Updated: 2022/11/24 02:23:41 by aanghel          ###   ########.fr       */
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
	int	i;
	int	len;

	i = -1;
	len = ft_strlen((char *)str);
	while (array[++i])
	{
		if (ft_strncmp(str, array[i], len) == 0)
			return (ft_substr(array[i], len, ft_strlen(array[i])));
	}
	return (NULL);
}
