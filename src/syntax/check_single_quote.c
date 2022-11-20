/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_single_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 18:51:47 by pcatapan          #+#    #+#             */
/*   Updated: 2022/11/20 18:53:32 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_check_single_quote(char *line, t_main *main, int i)
{
	if (line[i] == 39)
	{
		main->sin_quotes++;
		i++;
		while (line[i])
		{
			if (line[i] == 39)
			{
				main->sin_quotes++;
				break ;
			}
			i++;
		}
	}
	return (i);
}
