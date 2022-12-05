/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:49:28 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/05 16:55:55 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cd_path(t_main *main)
{
	int		i;
	char	*tmp;

	i = 0;
	while (main->copy_env[i])
	{
		if (ft_strncmp(main->copy_env[i], "PWD=", 4) == 0)
		{
			tmp = getcwd(NULL, 0);
			free(main->copy_env[i]);
			main->copy_env[i] = ft_strjoin("PWD=", tmp);
			free(tmp);
		}
		i++;
	}
}

void	ft_cd(t_token *token, t_main *main)
{
	char	*tmp;

	if (token->value[1] == NULL)
	{
		tmp = getenv("HOME");
		chdir(tmp);
		cd_path(main);
	}
	else if (chdir(token->value[1]) == -1)
	{
		g_exit = 1;
		printf(RED"cd: %s: " ERROR_FILE COLOR_RES, token->value[1]);
		printf("\n");
	}
	else
		cd_path(main);
}

void	ft_cd_or(t_token *token, t_main *main)
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
		ft_cd(token, main);
}

void	ft_check_cd(t_token *token, t_main *main)
{
	if (token->prev)
	{
		if (token->prev->or)
			ft_cd_or(token, main);
		else if (token->prev->and)
		{
			if (token->res)
				exit (1);
			else
				ft_cd(token, main);
		}
		else
			ft_cd(token, main);
	}
	else
		ft_cd(token, main);
}
