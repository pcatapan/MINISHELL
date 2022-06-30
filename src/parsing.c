/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:16:35 by pcatapan          #+#    #+#             */
/*   Updated: 2022/06/30 19:58:57 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_parsing(char *line)
{
	char	*segni;
	char	**rtr;
	int		i;

	i = 0;
	segni = malloc(sizeof(char) * 3);
	segni[0] = 34;
	segni[1] = 39;
	segni[2] = '\0';
	rtr = ft_split(line, segni);
	while (rtr[i])
	{
		printf("%s\n", rtr[i]);
		i++;
	}
	free(segni);
}
