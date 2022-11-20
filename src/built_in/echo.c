/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 19:10:04 by pcatapan          #+#    #+#             */
/*   Updated: 2022/11/20 19:41:53 by aanghel          ###   ########.fr       */
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
		token->value[i] = ft_strtrim2(token->value[i], '"');
		token->value[i] = ft_strtrim2(token->value[i], '\'');
		if (ft_strcmp(token->value[1], "$?"))
		{
			printf("%d\n", g_exit);
			exit(1);
		}
		else
		{
			printf("%s", token->value[i]);
			if (token->value[i + 1])
				printf(" ");
			i++;
		}
	}
	if (ft_strcmp(token->value[1], "-n") == 0)
		printf("\n");
}

void	ft_echo_or(t_token *token)
{
	if (token->res == 0)
	{
		if (token->next)
		{
			if (token->and)
				exit(0);
		}
		exit(1);
	}
	ft_echo(token);
}

void	ft_echo_and(t_token *token)
{
	if (token->res)
	{
		if (token->priority == 0)
			ft_echo(token);
		exit(1);
	}
	ft_echo(token);
}

void	ft_check_echo(t_token *token)
{
	if (token->prev)
	{
		if (token->prev->or)
			ft_echo_or(token);
		else if (token->prev->and)
			ft_echo_and(token);
		else
			ft_echo(token);
	}
	else
		ft_echo(token);
}
