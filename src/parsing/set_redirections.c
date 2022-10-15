/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:50:37 by aanghel           #+#    #+#             */
/*   Updated: 2022/10/15 16:51:13 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_set_redirections(char *line, t_token *token)
{
	int	i;

	i = 0;
	token = ft_return_head(token);
	while (token)
	{
		while (line[i])
		{
			if (line[i] == OUTPUT || line[i] == INPUT)
				break;
			i++;
		}
		i++;
		if (line[i] != OUTPUT && line[i - 1] == OUTPUT)
				token->output = true;
		else if (line[i] == OUTPUT)
			token->append = true;
		else if (line[i] != INPUT && line[i - 1] == INPUT)
			token->input = true;
		else if (line[i] == INPUT)
			token->heredoc = true;
		i++;
		if (!token->next)
			break;
		token = token->next;
	}
}

