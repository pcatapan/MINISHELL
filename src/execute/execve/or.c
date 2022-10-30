/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:44:32 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/30 23:49:49 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	ft_execve_or(t_token *token)
{
	if (token->res == 0)
	{
		if (token->next)
		{
			if (token->and)
				exit(1);
		}
		exit(1);
	}
	if (execve(token->command, token->value, token->main->copy_env))
	{
		printf(RED"%s: coomand not found\n"COLOR_RES, token->value[0]);
		exit(1);
	}
}
