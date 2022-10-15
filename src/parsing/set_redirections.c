/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:50:37 by aanghel           #+#    #+#             */
/*   Updated: 2022/10/15 17:19:13 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_set_redirections(t_token *token)
{
	token = ft_return_head(token);
	while (token)
	{
		if (ft_strcmp(token->value[1], ">"))
			token->output = true;
		if (ft_strcmp(token->value[1], ">>"))
			token->append = true;
		else if (ft_strcmp(token->value[1], "<"))
			token->input = true;
		else if (ft_strcmp(token->value[1], "<<"))
			token->heredoc = true;
		if (!token->next)
			break ;
		token = token->next;
	}
}
