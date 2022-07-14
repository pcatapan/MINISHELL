/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_op_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:59:43 by pcatapan          #+#    #+#             */
/*   Updated: 2022/07/14 00:00:02 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_set_op_logic(char *line, t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		while (line[i])
		{
			if (line[i] == '&' || line[i] == '|')
				break ;
			i++;
		}
		i++;
		if (line[i] == '&')
			token->and = true;
		else if (line[i] == '|')
			token->or = true;
		i++;
		if (!token->next)
			break ;
		token = token->next;
	}
}
