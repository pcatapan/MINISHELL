/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:28:58 by aanghel           #+#    #+#             */
/*   Updated: 2022/10/16 18:41:51 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**get_next_line(int fd)
{
	char	a[999999];
	char	buffer[1];
	char	*new_a;
	int		i;
	int		j;

	j = 0;
	a[i] = 0;
	while (read(fd, buffer, 1) == 1)
	{
		i = 0;
		while (read(fd, buffer, 1) == 1)
		{
			a[i] = buffer[0];
			a[i + 1] = '\0';
			if (a[i] == '\n')
				break ;
			i++;
		}
		j++;
	}
	new_a = malloc(i + 1);
	i = -1;
	while (a[++i])
		new_a[i] = a[i];
	new_a[i] = '\0';
	return (new_a);
}
