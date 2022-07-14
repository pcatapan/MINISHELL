/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_priority.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:00:25 by pcatapan          #+#    #+#             */
/*   Updated: 2022/07/14 05:42:42 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**ft_utils_set_priority(char *line, t_main *main)
{
	int	i;

	i = 0;
	while (line[i])
	{
		i = ft_check_single_quote(line, main, i);
		i = ft_check_double_quote(line, main, i);
		if (line[i] != 38 && line[i] != 59 && line[i] != 124 && line[i])
			i++;
		else if (line[i])
		{
			line[i] = 127;
			i++;
		}
	}
	return (ft_split_original(line, 127));
}

void	ft_set_priority(char *line, t_main *main, int brack)
{
	int		i;
	int		j;
	char	**tmp;

	i = -1;
	tmp = ft_utils_set_priority(line, main);
	while (tmp[++i])
	{
		j = -1;
		while (tmp[i][++j])
		{
			j = ft_check_double_quote(tmp[i], main, j);
			j = ft_check_single_quote(tmp[i], main, j);
			if (tmp[i][j] == '(')
				brack++;
			main->token->priority = brack;
			if (tmp[i][j] == ')')
			{
				brack--;
				break ;
			}
		}
		main->token = main->token->next;
	}
}
