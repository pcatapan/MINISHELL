/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_easy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:42:40 by pcatapan          #+#    #+#             */
/*   Updated: 2022/11/19 18:19:32 by fgrossi          ###   ########.fr       */
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
		j = 0;
		while (main->copy_env[j])
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
			j++;
		}
		i++;
	}
	ft_unset_exp(token, main);
}

void	ft_exit(t_token *token)
{
	int	i;

	i = 0;
	while (token->main->copy_env[i])
	{
		free(token->main->copy_env[i]);
		i++;
	}
	free(token->main->copy_env);
	printf(RED "\texit\n" COLOR_RES);
	exit((int)token->value[1]);
}
