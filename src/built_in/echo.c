/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 19:10:04 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/30 01:19:43 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_echo(t_token *token)
{
	int	i;

	i = 1;
	if (ft_strcmp(token->value[1], "-n") != 0)
		i++;
	while (token->value[i])
	{
		printf("%s", ft_clear_value(token->value[i]));
		if (token->value[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strcmp(token->value[1], "-n") == 0)
		printf("\n");
}

void	ft_check_echo(t_token *token)
{
	if (token->prev)
	{
		if (token->prev->or)
		{
			if (token->res == 0)
				exit(1);
			ft_echo(token);
		}
		else if (token->prev->and)
		{
			if (token->res)
				exit(1);
			ft_echo(token);
		}
		else
			ft_echo(token);
	}
	// else if (token->priority != 0)
	// 	ft_execve_priority(token);
	else
		ft_echo(token);
}

