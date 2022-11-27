/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 04:17:48 by pcatapan          #+#    #+#             */
/*   Updated: 2022/11/27 04:09:24 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strtrim2(char *str, char del)
{
	int		i;
	int		j;
	int		count;
	char	*rtr;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == del)
			count++;
	}
	i = -1;
	j = 0;
	rtr = (char *)malloc(sizeof(char) * (ft_strlen(str) - count + 1));
	if (!rtr)
		return (NULL);
	while (str[++i])
	{
		if (str[i] != del)
			rtr[j++] = str[i];
	}
	rtr[++j] = '\0';
	free(str);
	return (rtr);
}
