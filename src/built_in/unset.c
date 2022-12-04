/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:39:11 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/04 17:43:07 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_unset_exp(t_token *token, t_main *main)
{
	int	i;
	int	j;

	i = 1;
	while (token->value[i])
	{
		j = 0;
		while (main->export_env[j])
		{
			if (ft_strncmp(token->value[i], main->export_env[j], \
			ft_strlen(token->value[i])) == 0)
			{
				free(main->export_env[j]);
				main->export_env[j] = NULL;
				while (main->export_env[j + 1])
				{
					main->export_env[j] = main->export_env[j + 1];
					j++;
				}
				main->export_env[j] = NULL;
			}
			j++;
		}
		i++;
	}
}

void	ft_unset(t_token *token, t_main *main)
{
	int	i;
	int	j;

	i = 1;
	while (token->value[i])
	{
		j = -1;
		while (main->copy_env[++j])
		{
			if (ft_strncmp(token->value[i], main->copy_env[j], \
			ft_strlen(token->value[i])) == 0)
			{
				free(main->copy_env[j]);
				main->copy_env[j] = NULL;
				while (main->copy_env[j + 1])
				{
					main->copy_env[j] = main->copy_env[j + 1];
					j++;
				}
				main->copy_env[j] = NULL;
			}
		}
		i++;
	}
	ft_unset_exp(token, main);
}

void	ft_echo_unset(t_token *token, t_main *main)
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
		ft_unset(token, main);
}

void	ft_check_unset(t_token *token, t_main *main)
{
	if (token->prev)
	{
		if (token->prev->or)
			ft_echo_unset(token, main);
		else if (token->prev->and)
		{
			if (token->res)
				exit (1);
			else
				ft_unset(token, main);
		}
		else
			ft_unset(token, main);
	}
	else
		ft_unset(token, main);
}
