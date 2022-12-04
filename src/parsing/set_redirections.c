/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:54:54 by aanghel           #+#    #+#             */
/*   Updated: 2022/12/04 23:37:00 by pcatapan         ###   ########.fr       */
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
			if (!token->name_file)
				token->name_file = ft_strdup(token->value[i + 1]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_set_bool_redir(t_token *token, char *redir)
{
	int	i;

	i = 0;
	while (token->value[i])
	{
		if (ft_strcmp(token->value[i], redir))
			return (1);
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
		if (ft_search_redir(token, ">>") == 1)
			token->append = true;
		if (ft_search_redir(token, "<") == 1)
			token->input = true;
		if (ft_set_bool_redir(token, "<<") == 1)
			token->heredoc = true;
		if (!token->next)
			break ;
		token = token->next;
	}
}
