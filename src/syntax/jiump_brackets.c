/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jiump_brackets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 18:23:29 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/03 22:53:12 by fgrossi          ###   ########.fr       */
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

int	ft_check_expand(char *line, int i)
{
	bool	dollar;
	int		count;

	dollar = FALSE;
	count = 1;
	if (line[i] == '$')
		dollar = TRUE;
	else
		return (0);
	if (((line[i + 1] == '$' || line[i - 1] == '$') && dollar) \
			|| ft_strlen(line) == 1)
		return (0);
	while (i > 0)
	{
		if (line[i] == '"')
			count++;
		i--;
	}
	if ((count % 2) == 0 && !ft_strchr(line, '"'))
		return (0);
	if (dollar)
		return (1);
	return (0);
}
