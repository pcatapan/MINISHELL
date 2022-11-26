/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_op_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:59:43 by pcatapan          #+#    #+#             */
/*   Updated: 2022/11/26 02:44:49 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_support_set_op(char *line, int i, t_token *token)
{
	while (line[i])
	{
		i = ft_check_double_quote(line, token->main, i);
		i = ft_check_single_quote(line, token->main, i);
		if (line[i] == '&' || line[i] == '|')
			break ;
		i++;
	}
	return (i);
}

void	ft_set_op_logic(char *line, t_token *token)
{
	int	i;

	i = 0;
	token = ft_return_head(token);
	while (token)
	{
		i = ft_support_set_op(line, i, token);
		i++;
		if (line[i] == '&')
			token->and = true;
		else if (line[i] == '|')
			token->or = true;
		else if (line[i - 1] == '|' && line[i] != '|')
			token->pipe = true;
		i++;
		if (!token->next)
			break ;
		token = token->next;
	}
}
