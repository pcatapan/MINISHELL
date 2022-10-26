/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:54:54 by aanghel           #+#    #+#             */
/*   Updated: 2022/10/26 18:11:08 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_search_redir(t_token *token, char *redir)
{
	int	i;

	i = 0;
	while (token->value[i])
	{
		if (ft_strcmp(token->value[i], redir))
		{
			token->name_file = ft_strdup(token->value[i + 1]);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_set_redirections(t_token *token)
{
	token = ft_return_head(token);
	while (token)
	{
		if (ft_search_redir(token, ">") == 1)
			token->output = true;
		else if (ft_search_redir(token, ">>") == 1)
			token->append = true;
		else if (ft_search_redir(token, "<") == 1)
			token->input = true;
		else if (ft_search_redir(token, "<<") == 1)
			token->heredoc = true;
		if (!token->next)
			break ;
		token = token->next;
	}
}
