/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:39:38 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/12 15:44:00 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	j;

	j = 0;
	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen((char *)s1);
	while (i && ft_strchr(set, s1[i - 1]))
		i--;
	return (ft_substr(s1, 0, i));
}