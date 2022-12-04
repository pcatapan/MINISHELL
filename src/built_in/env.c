/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:46:27 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/04 17:49:06 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env(t_main *main)
{
	int	i;

	i = 0;
	while (main->copy_env[i])
	{
		printf("%s\n", main->copy_env[i]);
		i++;
	}
}

void	ft_env_or(t_token *token, t_main *main)
{
	if (token->res == 0)
	{
		if (token->next)
		{
			if (token->and)
				;
		}
	}
	else
		ft_env(main);
}

void	ft_check_env(t_token *token, t_main *main)
{
	if (token->prev)
	{
		if (token->prev->or)
			ft_env_or(token, main);
		else if (token->prev->and)
		{
			if (token->res)
				exit (1);
			else
				ft_env(main);
		}
		else
			ft_env(main);
	}
	else
		ft_env(main);
}
