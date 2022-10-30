/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:44:12 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/30 23:53:47 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	ft_execve_and(t_token *token)
{
	if (token->res)
	{
		if (token->priority == 0)
		{
			if (execve(token->command, token->value, token->main->copy_env))
			{
				printf(RED"%s: command not found\n"COLOR_RES, token->value[0]);
				exit(1);
			}
		}
		exit(1);
	}
	if (execve(token->command, token->value, token->main->copy_env))
	{
		printf(RED"%s: command not found\n"COLOR_RES, token->value[0]);
		exit(1);
	}
}
