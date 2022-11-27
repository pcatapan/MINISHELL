/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:28:58 by aanghel           #+#    #+#             */
/*   Updated: 2022/10/16 21:45:15 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**ft_get_next_line(int fd, char *file)
{
	int		i;
	char	c;
	char	**rtr;
	char	*buffer;

	i = 0;
	buffer = malloc (9999);
	fd = open(file, O_CREAT | O_RDONLY, 0644);
	while (read(fd, &c, 1) > 0)
	{
		buffer[i] = c;
		i++;
		if (c == '\0')
			break ;
	}
	buffer[i] = '\0';
	rtr = ft_split_original(buffer, '\n');
	return (rtr);
}
