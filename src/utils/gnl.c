/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:28:58 by aanghel           #+#    #+#             */
/*   Updated: 2022/10/16 21:08:00 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**ft_get_next_line(int fd)
{
	char	array[999999];
	char	buffer[1];
	char	*new_a;
	int		i;
	char	**set;

	i = 0;
	array[i] = 0;
	while (read(fd, buffer, 1) == 1)
	{
		printf("SONO QUI\n");
		array[i] = buffer[0];
		array[i + 1] = '\0';
		if (array[i] == '\0')
			break ;
		i++;
	}
	new_a = malloc(i + 1);
	i = -1;
	while (a[++i])
		new_a[i] = a[i];
	new_a[i] = '\0';
	set = ft_split_original(new_a, '\n');
	return (set);
}
