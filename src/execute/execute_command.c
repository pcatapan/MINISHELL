/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 22:11:00 by fgrossi           #+#    #+#             */
/*   Updated: 2022/12/04 23:25:15 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_execute_redi(t_token *token, t_main *main)
{
	if (!main->token->heredoc)
		ft_execute_dollar(main->token, main);
	if (ft_strchr(main->token->value[0], '=') \
		&& ft_check_envi(main->token->value[0]))
		main->token = ft_execute_enviroment(main->token, main->token->value[0]);
	else if (ft_check_builtin(main->token) && !main->redirections)
		main->token = ft_execute_builtin(main->token, main);
	else
		main->token = ft_execute_exeve(main->token, main);
	ft_check_dir(main);
	exit(token->res);
}

void	ft_execute_command(t_main *main)
{
	int	lstsize;

	main->count = 0;
	lstsize = ft_lstsize(main->token);
	main->token = ft_return_head(main->token);
	while (main->count < lstsize)
	{
		if (!main->token->heredoc)
			ft_execute_dollar(main->token, main);
		if (ft_strchr(main->token->value[0], '=') \
			&& ft_check_envi(main->token->value[0]))
			main->token = \
				ft_execute_enviroment(main->token, main->token->value[0]);
		else if (main->token->input || main->token->append || \
			main->token->output || main->token->heredoc || main->redirections)
			main->token = ft_redirections(main->token, main);
		else if (ft_check_builtin(main->token) && !main->redirections)
			main->token = ft_execute_builtin(main->token, main);
		else
			main->token = ft_execute_exeve(main->token, main);
		ft_check_dir(main);
		main->count++;
	}
}
