/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jiump_brackets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 18:23:29 by pcatapan          #+#    #+#             */
/*   Updated: 2022/11/20 19:17:50 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_jump_brackets(char *line, int i)
{
	if (line[i] == 28)
	{
		i++;
		while (line[i])
		{
			if (line[i] == 29)
				break ;
			i++;
		}
	}
	return (i);
}
