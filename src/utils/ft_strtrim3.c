/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 01:02:30 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/03 19:49:27 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief This funcion del all char in str *del
 * The synatx of char *del is "A B C" with this *del
 * the funcion del all A B C in the char *str
 * 
 * @param str Str to find the char to del
 * @param del Str with the char to del
 * @return char* Str clear of char del
 */
char	*ft_strtrim3(char *str, char *del)
{
	int		i;
	char	**matrix;
	char	*rtr;

	i = 0;
	matrix = ft_split_original(del, 32);
	while (1)
	{
		rtr = ft_strtrim2(str, matrix[i][0]);
		if (!ft_strchr(str, matrix[i][0]))
		{
			i++;
			if (!matrix[i])
				break ;
		}
		str = ft_strdup(rtr);
		free(rtr);
	}
	ft_free_matrix(matrix);
	return (rtr);
}
