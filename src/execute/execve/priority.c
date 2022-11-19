/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:44:36 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/30 23:59:24 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_token	*ft_priority(t_token *token, int lvl, t_main *main)
{
	pid_t	pidchild;
	int		lstsize;

	lstsize = ft_lstsize_this(token);
	// token = ft_return_head(token);
	// ft_print_lst(token);
	while (main->count <= lstsize)
	{
		if (token->priority != lvl)
			token = ft_priority(token, token->priority, main);
		ft_execute_dollar(token);
		if (ft_strchr(token->value[0], '=') && ft_check_envi(token->value[0]))
			token = ft_execute_enviroment(token, token->value[0]);
		// else if (ft_check_builtin(token) && !redirections)
		// 	token = ft_execute_builtin(token);
		else if (token->main->redirections)
			token = ft_redirections(token, token->main);
		else // Qui entra se il comando bultin é errato o se non é da gestirte
			token = ft_execute_exeve(token, main);
		main->count++;
	}
	return (token);
}
