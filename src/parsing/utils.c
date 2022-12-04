/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:01:24 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/04 23:52:10 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*ft_return_head(t_token *list)
{
	while (list)
	{
		if (!list->prev)
			break ;
		list = list->prev;
	}
	return (list);
}

int	ft_support_parsing(char *line, t_main *main, int i)
{	
	i = ft_check_single_quote(line, main, i);
	i = ft_check_double_quote(line, main, i);
	i = ft_jump_brackets(line, i);
	return (i);
}

int	ft_count_array(char *line, t_main *main)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == 39 || line[i] == 34)
			count++;
		i = ft_check_double_quote(line, main, i);
		i = ft_check_single_quote(line, main, i);
		if (line[i] != 32 && line[i - 1] == 32)
			count++;
		i++;
	}
	return (count);
}
