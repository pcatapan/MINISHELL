/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_comand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:44:58 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/03 22:11:25 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_qualcosa(t_token *token, t_main *main)
{
	if (ft_check_builtin(token))
		token = ft_execute_builtin(token, main);
	else if (ft_strchr(token->value[0], '=') && ft_check_envi(token->value[0]))
		token = ft_execute_enviroment(token, token->value[0]);
	else
		token = ft_execute_exeve(token, main);
	exit(token->res);
}

void	ft_exceve(t_token *token)
{
	if (token->prev)
	{
		if (token->prev->or)
			ft_execve_or(token);
		else if (token->prev->and)
			ft_execve_and(token);
		if (execve(token->command, token->value, token->main->copy_env))
		{
			printf(RED"%s: command not found\n"COLOR_RES, token->value[0]);
			g_exit = 127;
			exit(127);
		}
	}
	else
	{
		if (execve(token->command, token->value, token->main->copy_env))
		{
			printf(RED"%s: command not found\n"COLOR_RES, token->value[0]);
			g_exit = 127;
			exit(127);
		}
	}
	exit(1);
}
