/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_priority.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:00:25 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/11 19:32:20 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**ft_utils_set_priority(char *line, t_main *main)
{
	int	i;
	char *dup;

	i = 0;
	dup = ft_strdup(line);
	while (dup[i])
	{
		i = ft_check_single_quote(dup, main, i);
		i = ft_check_double_quote(dup, main, i);
		if (dup[i] != 38 && dup[i] != 59 && dup[i] != 124)
			i++;
		else if (dup[i])
		{
			dup[i] = 127;
			i++;
		}
	}
	return (ft_split_original(dup, 127));
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
		if (main->token->next)
			main->token = main->token->next;
	}
}
