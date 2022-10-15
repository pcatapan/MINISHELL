/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:50:37 by aanghel           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/10/15 17:19:13 by aanghel          ###   ########.fr       */
=======
/*   Updated: 2022/10/15 16:51:13 by pcatapan         ###   ########.fr       */
>>>>>>> refs/remotes/origin/master
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
