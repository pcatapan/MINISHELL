/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:44:36 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/26 19:51:29 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	ft_execve_priority(t_token *token)
{
	if (token->priority == (token->prev->priority - 2))
	{
		printf(RED"%s: command not found\n"COLOR_RES, token->value[0]);
		exit(1);
	}
	ft_qualcosa(token);
}
